#include "dispatcher.h"

Dispatcher::Dispatcher() : _engine(_seed()), _char_list("abcDEFghijklmnop~_/\\"), _random_angle(0, 71) {}

int Dispatcher::get_angle() {

  std::unique_lock<std::mutex> ul(_mutex);
  int angle;

  do
    angle = _random_angle(_engine) * 5;
  while (std::find(_used_angles.begin(), _used_angles.end(), angle) != _used_angles.end());

  _used_angles.emplace_back(angle);
  return angle;
}

void Dispatcher::release_angle(int angle) {

  std::unique_lock<std::mutex> ul(_mutex);
  _used_angles.erase(std::remove(_used_angles.begin(), _used_angles.end(), angle));
}

char Dispatcher::get_char() {

  // FIX: Add a security in case of more threads than char ?
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<int> random_txt(0, _char_list.size() - 1);
  std::string::iterator it = std::next(_char_list.begin(), random_txt(_engine));

  char selected_char = *it;
  _char_list.erase(it);

  return selected_char;
};

void Dispatcher::release_char(char c) {

  std::unique_lock<std::mutex> ul(_mutex);
  _char_list += c;
}
