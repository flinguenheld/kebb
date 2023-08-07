#include "dispatcher.h"

Dispatcher::Dispatcher(std::shared_ptr<OptionFile> options) : _engine(_seed()), _number_of_chars(0) {

  if (options->get().letters) {
    for (uint16_t i = 10; i < 36; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }
  if (options->get().capitals) {
    for (uint16_t i = 100; i < 126; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }
  if (options->get().numbers) {
    for (uint16_t i = 500; i < 510; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }
  if (options->get().symbols) {
    for (uint16_t i = 1000; i < 1032; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }
  if (options->get().french_extras) {

    uint16_t max = 2016;
    if (options->get().layout == "FR") // Avoid æ œ // NOTE: With other layouts ?
      max = 2114;

    for (uint16_t i = 2000; i < 2014; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }

  if (options->get().french_extra_caps) {

    uint16_t max = 2115;
    if (options->get().layout == "FR") // Avoid æ œ
      max = 2113;

    for (uint16_t i = 2100; i < max; ++i) {
      _keycodes.emplace_back(i);
      ++_number_of_chars;
    }
  }

  for (uint16_t i = 0; i < 360; i += 5)
    _angles.emplace_back(i);
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
