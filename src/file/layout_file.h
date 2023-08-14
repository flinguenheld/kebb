#ifndef LAYOUT_FILE_H
#define LAYOUT_FILE_H

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

struct Key {

  std::string text;
  uint32_t sym;
  bool shift = false;
  bool alt = false;
  bool altgr = false;
  uint16_t dead = 0;
  uint16_t is_dead = 0;
  uint16_t type = 0;
};

enum class TypeChar {
  Ignored = 0,
  Letter = 1,
  Letter_cap = 2,
  Number = 3,
  Symbol = 4,
  Symbol_plus = 5,
  Extra = 6,
  Extra_cap = 7,
};

/*
 * Used to list and read layout files.
 * set_layout() fills the vector _keys which is used by the controller to check user's entries.
 */
class LayoutFile {
public:
  LayoutFile();

  std::vector<std::string> list_layouts() const;
  void set_layout(const std::string &file_name);

  const std::vector<Key> &keys() const;
  bool are_there(const std::string &file_name, TypeChar) const;

private:
  std::string _path;
  const char delimiter;

  std::vector<Key> _keys;
};

#endif // !LAYOUT_FILE_H
