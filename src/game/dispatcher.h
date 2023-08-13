#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "file/layout_file.h"
#include "file/option_file.h"
#include <iostream>
#include <memory>
#include <mutex>
#include <random>
#include <vector>

/*
 * Dispatcher class: its role is to distribute random characters and angles to threads in a
 * safe way.
 * Once a thread has taken a character/angle, they are erase from lists.
 * This latter has to get it back with the relase methods.
 */
class Dispatcher {
public:
  Dispatcher(std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts);

  uint16_t get_angle();
  void release_angle(uint16_t angle);

  void get_character(std::string &text);
  void release_character(std::string &&k);

  uint16_t number_of_chars() const;

private:
  std::shared_ptr<LayoutFile> _layouts;
  void add(uint16_t key_type);

  std::vector<uint16_t> _angles;
  std::vector<std::string> _characters;

  uint16_t _number_of_chars;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
};

#endif // DISPATCHER_H
