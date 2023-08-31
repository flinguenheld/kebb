#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include "file.h"

struct Options {
  std::string resolution = "480-20";
  std::string layout = "qwerty";

  uint16_t timer_countdown = 30;
  uint16_t timer_speed = 6;
  uint16_t timer_nb_targets = 5;

  uint16_t survival_nb_targets = 5;
  uint16_t survival_speed = 10;
  std::string survival_difficulty = "normal";
  uint16_t survival_max_fail = 10; // FIX: Adapt
  uint16_t survival_max_miss = 10;
  uint16_t survival_next_level = 50;

  uint16_t last_mode = 10;
  bool letters = true;
  bool capitals = false;
  bool numbers = true;
  bool symbols = false;
  bool symbols_plus = false;
  bool extras = false;
  bool extra_caps = false;
};

/*
 * Allows to manage options which are stored in a struct.
 * The constructor reads the file to fill the struct.
 * Then the destructor write the file with the updated data.
 */
class OptionFile : public File {
public:
  OptionFile();
  ~OptionFile();

  const Options &get() const;
  Options &set();

private:
  Options _options;

  void save() const;
  void read();
};

#endif // !OPTION_FILE_H
