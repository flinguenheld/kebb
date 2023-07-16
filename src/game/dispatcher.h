#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "option/option_file.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <string>
#include <vector>

/*
 * Dispatcher class: its role is to distribute random keycodes and angles to threads in a
 * safe way.
 * Once a thread has taken a keycode/angle, they are erase from lists.
 * This latter has to get it back with relase methods.
 */
class Dispatcher {
public:
  Dispatcher(std::shared_ptr<OptionFile> options);

  uint16_t get_angle();
  void release_angle(uint16_t angle);

  uint16_t get_keycode();
  void release_keycode(uint16_t k);

  uint16_t number_of_chars() const;

private:
  std::vector<uint16_t> _angles;
  std::vector<uint16_t> _keycodes;

  uint16_t _number_of_chars;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
};

#endif // DISPATCHER_H
