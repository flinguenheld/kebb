#include "dispatcher.h"

Dispatcher::Dispatcher(std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts)
    : _layouts(layouts), _engine(_seed()), _number_of_chars(0) {

  if (options->get().letters)
    add(1);

  if (options->get().capitals)
    add(2);

  if (options->get().numbers)
    add(3);

  if (options->get().symbols)
    add(4);

  if (options->get().extras)
    add(5);

  if (options->get().extra_caps) // FIX: Rename !!!
    add(6);

  for (uint16_t i = 0; i < 360; i += 10) // NOTE: 36 threads maxi !
    _angles.emplace_back(i);
}

/*
 * Add a type of letters (see layouts)
 */
void Dispatcher::add(uint16_t key_type) {

  for (const auto &k : _layouts->keys()) {
    if (k.type == key_type) {
      _keycodes.emplace_back(k.kebb);
      ++_number_of_chars;
    }
  }
}

/*
 * Allow to limit the amount of threads
 */
uint16_t Dispatcher::number_of_chars() const { return _number_of_chars; }

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
