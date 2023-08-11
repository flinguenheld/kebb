#include "file.h"

// TODO: Windows path ?
File::File(std::string &&file_name) {

#ifdef RELEASE_LINUX
  std::string path = std::string(getenv("HOME")) + "/.kebb";
#else
  std::string path = "./files_kebb";
#endif

  if (!std::filesystem::exists(path))
    std::filesystem::create_directory(path);

  _filename = path + "/" + std::move(file_name);
}
