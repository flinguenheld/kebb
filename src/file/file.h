#ifndef FILE_H
#define FILE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

/*
 *
 */
class File {
public:
  File(std::string &&file_name);

protected:
  std::string _filename;
};

#endif // !FILE_H
