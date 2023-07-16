#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include <fstream>
#include <iostream>
#include <string>

enum class OptionName {
  Resolution,
  Layout,
  Target,
  Countdown,
  Speed,
  Letters,
  Capitals,
  Number,
  Symbol,
};

/*
 * Allows to read and save the option file.
 * All options are numbers.
 */
class OptionFile {
public:
  OptionFile();

  void save() const;
  void read();

  void set(OptionName type, int16_t val);
  int16_t get(OptionName type);

private:
  const std::string _filename;

  uint16_t _resolution;
  uint16_t _layout;

  uint16_t _nb_targets;
  uint16_t _countdown;
  uint16_t _speed;

  bool _letters;
  bool _capitals;
  bool _numbers;
  bool _symbols;
};

#endif // !OPTION_FILE_H
