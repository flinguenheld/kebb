#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <algorithm>
#include <cstdint>
#include <iostream>
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
  Dispatcher();

  uint16_t get_angle();
  void release_angle(uint16_t angle);

  uint16_t get_keycode();
  void release_keycode(uint16_t k);

private:
  std::vector<uint16_t> _angles;
  std::vector<uint16_t> _keycodes;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
};

#endif // DISPATCHER_H
