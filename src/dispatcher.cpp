#include "dispatcher.h"

// NOTE: Add a security in case of more threads than keycodes ?
// TODO: Set the list according to future options

Dispatcher::Dispatcher() : _engine(_seed()) {

  for (uint16_t i = 10; i < 36; ++i) // Add Letters
    _keycodes.emplace_back(i);
  for (uint16_t i = 100; i < 126; ++i) // Add Caps
    _keycodes.emplace_back(i);
  for (uint16_t i = 500; i < 510; ++i) // Add Numbers
    _keycodes.emplace_back(i);
  for (uint16_t i = 1000; i < 1032; ++i) // Add symbols
    _keycodes.emplace_back(i);

  for (uint16_t i = 0; i < 360; i += 5)
    _angles.emplace_back(i);
}

/*
 * Select an angle in the list, erase and return it.
 */
uint16_t Dispatcher::get_angle() {
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<uint16_t> random(0, _angles.size() - 1);
  std::vector<uint16_t>::iterator it = std::next(_angles.begin(), random(_engine));

  const uint16_t selected_angle = *it;
  _angles.erase(it);

  return selected_angle;
}

/*
 * Get it back in the angle list
 */
void Dispatcher::release_angle(uint16_t angle) {
  std::unique_lock<std::mutex> ul(_mutex);
  _angles.emplace_back(angle);
}

/*
 * Select a keycode in the list, erase and return it.
 */
uint16_t Dispatcher::get_keycode() {
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<uint16_t> random_keycodes(0, _keycodes.size() - 1);
  std::vector<uint16_t>::iterator it = std::next(_keycodes.begin(), random_keycodes(_engine));

  const uint16_t selected_keycode = *it;
  _keycodes.erase(it);

  return selected_keycode;
};

/*
 * Get it back in the char list
 */
void Dispatcher::release_keycode(uint16_t k) {
  std::unique_lock<std::mutex> ul(_mutex);
  _keycodes.emplace_back(k);
}
