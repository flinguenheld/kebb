#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Key {

  uint16_t kebb = 0;
  uint16_t sym;
  bool shift = false;
  bool alt = false;
  bool altgr = false;
  uint16_t dead = 0;
  bool is_dead = false;
};

/*
 *
 */
class Language {
public:
  Language(std::string &&file_name);

  void read_file(std::vector<Key> &keys);

protected:
  std::string _filename;
  char delimiter;
};

#endif // !LANGUAGE_H
