#include "dispatcher.h"

// clang-format off
Dispatcher::Dispatcher() :
  _engine(_seed()),
  _letters("abcdefghijklmnopqrstuvwxyz"),
  _capitals("ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
  _symbols("!\"#$%&'*+,_./:;<>=?@^-`|~\\[]{}()"),
  _numbers("0123456789")
{
  // clang-format on

  // NOTE: Add a security in case of more threads than char ?
  // TODO: Set the list according to future options

  _char_list = _letters + _capitals + _numbers + _symbols;

  for (int i = 0; i < 360; i += 5)
    _angles.emplace_back(i);
}

/*
 * Select an angle in the list, erase and return it.
 */
int Dispatcher::get_angle() {
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<int> random(0, _angles.size() - 1);
  std::vector<int>::iterator it = std::next(_angles.begin(), random(_engine));

  const int selected_angle = *it;
  _angles.erase(it);

  return selected_angle;
}

/*
 * Get it back in the angle list
 */
void Dispatcher::release_angle(int angle) {
  std::unique_lock<std::mutex> ul(_mutex);
  _angles.emplace_back(angle);
}

/*
 * Select a char in the list, erase and return it.
 */
char Dispatcher::get_char() {
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<int> random_txt(0, _char_list.size() - 1);
  std::string::iterator it = std::next(_char_list.begin(), random_txt(_engine));

  const char selected_char = *it;
  _char_list.erase(it);

  return selected_char;
};

/*
 * Get it back in the char list
 */
void Dispatcher::release_char(char c) {
  std::unique_lock<std::mutex> ul(_mutex);
  _char_list += c;
}
