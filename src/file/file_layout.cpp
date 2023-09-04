#include "file_layout.h"

// TODO: Windows path ?
LayoutFile::LayoutFile() : delimiter(',') {

#ifdef RELEASE_LINUX
  _path = "/usr/share/kebb/layout";
#else
  _path = "./layout";
#endif
}

// ----------------------------------------------------------------------------------------------------
// LIST LAYOUT FOLDER ---------------------------------------------------------------------------------
std::vector<std::string> LayoutFile::list_layouts() const {

  const std::filesystem::path folder{_path};
  std::vector<std::string> file_names;

  for (auto const &dir_entry : std::filesystem::directory_iterator{folder})
    file_names.emplace_back(dir_entry.path().filename());

  return file_names;
}

// ----------------------------------------------------------------------------------------------------
// READ LAYOUT FILE -----------------------------------------------------------------------------------
void LayoutFile::set_layout(const std::string &file_name) {

  _keys.clear();

  auto file = std::ifstream(_path + "/" + file_name, std::ios::in);
  if (!file.is_open()) {
    std::cout << "Error: Layout file '" << file_name << "' doesn't exist!" << std::endl;

  } else {

    std::string line;
    while (getline(file, line)) {

      if (line.length() != 0) {
        if (line[0] != '/' && line[1] != '/') {

          Key new_key;

          size_t pos = 0;
          uint16_t field_index = 0;
          std::string field;

          while ((pos = line.find(delimiter)) != std::string::npos) {

            field = line.substr(0, pos);

            switch (field_index) {
            case 0:
              if (field == "comma") // , is the separator
                field = ",";

              new_key.text = field;
              break;
            case 1:
              new_key.sym = std::stoi(field);
              break;
            case 2:
              new_key.shift = std::stoi(field);
              break;
            case 3:
              new_key.alt = std::stoi(field);
              break;
            case 4:
              new_key.altgr = std::stoi(field);
              break;
            case 5:
              new_key.dead = std::stoi(field);
              break;
            case 6:
              new_key.is_dead = std::stoi(field);
              break;
            case 7:
              new_key.type = std::stoi(field);
            }

            line.erase(0, pos + 1);
            ++field_index;
          }

          _keys.emplace_back(new_key);
        }
      }
    }
  }

  // for (auto &k : _keys) {
  //   std::cout << "key: "
  //             << " " << k.text << " " << k.shift << " type: " << k.type << std::endl;
  // }
}

/*
 * Open the file to read the first line.
 * Then check if the value of t is in the line.
 */
bool LayoutFile::are_there(const std::string &file_name, TypeChar t) const {

  auto file = std::ifstream(_path + "/" + file_name, std::ios::in);
  if (file.is_open()) {

    std::string line;
    getline(file, line);

    return (line.find(std::to_string((uint16_t)t)) != std::string::npos);
  }

  return false;
}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
const std::vector<Key> &LayoutFile::keys() const { return _keys; }
