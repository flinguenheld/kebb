#include "dispatcher.h"
#include "file/layout_file.h"
#include <cstdint>
#include <string>

Dispatcher::Dispatcher(std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts)
    : _layouts(layouts), _engine(_seed()), _number_of_chars(0) {

  if (options->get().letters)
    add(uint16_t(TypeChar::Letter));

  if (options->get().capitals)
    add(uint16_t(TypeChar::Letter_cap));

  if (options->get().numbers)
    add(uint16_t(TypeChar::Number));

  if (options->get().symbols)
    add(uint16_t(TypeChar::Symbol));

  if (options->get().symbols_plus)
    add(uint16_t(TypeChar::Symbol_plus));

  if (options->get().extras)
    add(uint16_t(TypeChar::Extra));

  if (options->get().extra_caps)
    add(uint16_t(TypeChar::Extra_cap));

  for (uint16_t i = 0; i < 360; i += 12) // NOTE: 30 threads maxi !
    _angles.emplace_back(i);
}

/*
 * Add a type of letters (see layouts)
 */
void Dispatcher::add(uint16_t key_type) {

  for (const auto &k : _layouts->keys()) {
    if (k.type == key_type) {
      _characters.emplace_back(k.text);
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
 * Select a character in the list, erase and move it.
 */
void Dispatcher::get_character(std::string &text) {
  std::unique_lock<std::mutex> ul(_mutex);

  std::uniform_int_distribution<uint16_t> random_char(0, _characters.size() - 1);
  std::vector<std::string>::iterator it = std::next(_characters.begin(), random_char(_engine));

  text = std::move(*it);
  _characters.erase(it);
};

/*
 * Get it back in the char list
 */
void Dispatcher::release_character(std::string &&k) {
  std::unique_lock<std::mutex> ul(_mutex);
  _characters.emplace_back(std::move(k));
}
