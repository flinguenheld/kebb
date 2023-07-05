#include "dispatcher.h"
#include <algorithm>
#include <iostream>
#include <mutex>
#include <string>

Dispatcher::Dispatcher()
    // : _engine(_seed()), _chars{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}, _random_angle(0, 359),
    : _engine(_seed()), _char_list("abcdefghijklmnop~_/\\"), _random_angle(0, 359),
      _random_txt(0, _char_list.size() - 1) {}

int Dispatcher::get_angle() {

  std::unique_lock<std::mutex> ul(_mutex);
  int angle;

  do
    angle = _random_angle(_engine);
  while (std::find(_used_angles.begin(), _used_angles.end(), angle) != _used_angles.end());

  _used_angles.emplace_back(angle);
  return angle;
}

void Dispatcher::release_angle(int angle) {

  std::unique_lock<std::mutex> ul(_mutex);
  _used_angles.erase(std::remove(_used_angles.begin(), _used_angles.end(), angle));
}

std::string Dispatcher::get_txt() {

  int attempts(0);
  std::string new_text;

  do {
    new_text = _char_list[_random_txt(_engine)];

    attempts++;
    if (attempts >= 1)
      break;
  } while (std::find(_used_texts.begin(), _used_texts.end(), new_text) != _used_texts.end());

  std::cout << "lettre : " << new_text << std::endl;

  _used_texts.emplace_back(new_text);
  return new_text;
};
void Dispatcher::release_txt(std::string letter) {

  // std::unique_lock<std::mutex> ul(_mutex);
  // for (auto it(_used_char.begin()); it != _used_char.end(); ++it) {
  //   if (*it == letter) {
  //     _used_char.erase(it);
  //     break;
  //   }
  // }
}
