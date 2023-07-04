#include "dispatcher.h"
#include <algorithm>

Dispatcher::Dispatcher()
    : _engine(_seed()), _chars{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'}, _random_angle(0, 359),
      _random_txt(0, _chars.size()) {}

int Dispatcher::get_angle() {

  int angle;

  do
    angle = _random_angle(_engine);
  while (std::find(_used_angles.begin(), _used_angles.end(), angle) != _used_angles.end());

  _used_angles.emplace_back(angle);
  return angle;
}

void Dispatcher::release_angle(int angle) {
  _used_angles.erase(std::remove(_used_angles.begin(), _used_angles.end(), angle));
}

std::string Dispatcher::get_txt() { return "a"; };
void Dispatcher::release_txt() {}
