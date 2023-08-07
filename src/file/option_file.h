#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include "file.h"
#include <cstdint>

struct Options {
  std::string resolution = "480-20";
  std::string layout = "US";
  uint16_t nb_targets = 5;
  uint16_t countdown = 30;
  uint16_t speed = 20;
  uint16_t survival_difficulty = 2;
  uint16_t last_mod = 10;
  bool letters = true;
  bool capitals = false;
  bool numbers = true;
  bool symbols = false;
  bool french_extras = false;
  bool french_extra_caps = false;
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
