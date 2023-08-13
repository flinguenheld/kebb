#include "language.h"
#include <iostream>
#include <string>

// TODO: Windows path ?
Language::Language(std::string &&file_name) : delimiter(',') {

#ifdef RELEASE_LINUX
  std::string path = "/usr/share/kebb/test_qwerty.kebb";
#else
  std::string path = "./languages";
#endif

  if (!std::filesystem::exists(path))
    std::cout << "ERROR LANGUAGE FILE !" << std::endl;

  _filename = path + "/" + std::move(file_name);
}

void Language::read_file(std::vector<Key> &keys) {

  auto file = std::ifstream(_filename, std::ios::in);

  if (file.is_open()) {

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
              // Letter
              break;
            case 1:
              new_key.kebb = std::stoi(field);
              break;
            case 2:
              new_key.sym = std::stoi(field);
              break;
            case 3:
              new_key.shift = std::stoi(field);
              break;
            case 4:
              new_key.alt = std::stoi(field);
              break;
            case 5:
              new_key.altgr = std::stoi(field);
              break;
            case 6:
              new_key.dead = std::stoi(field);
              break;
            case 7:
              new_key.is_dead = std::stoi(field);
              break;
            }

            line.erase(0, pos + 1);
            ++field_index;
          }

          keys.emplace_back(new_key);
        }
      }
    }
  }

  for (auto &k : keys) {
    std::cout << "key: " << k.kebb << " " << k.sym << " " << k.shift << std::endl;
  }
}
