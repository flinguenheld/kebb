#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

enum class OptionName {
  Layout,
  Target,
  Countdown,
  Speed,
  Letters,
  Capitals,
  Number,
  Symbol,
};

class OptionFile {

public:
  OptionFile();

  template <typename T> void set_value(OptionName type, T val) {
    switch (type) {
    case OptionName::Layout:
      _layout = val;
      break;
    case OptionName::Target:
      _nb_targets = val;
      break;
    case OptionName::Countdown:
      _countdown = val;
      break;
    case OptionName::Speed:
      _speed = val;
      break;
    case OptionName::Letters:
      _letters = val;
      break;
    case OptionName::Capitals:
      _capitals = val;
      break;
    case OptionName::Number:
      _numbers = val;
      break;
    default:
      _symbols = val;
    }
  }

  template <typename T> T get_value(OptionName type) {
    switch (type) {
    case OptionName::Layout:
      return _layout;
    case OptionName::Target:
      return _nb_targets;
    case OptionName::Countdown:
      return _countdown;
    case OptionName::Speed:
      return _speed;
    case OptionName::Letters:
      return _letters;
    case OptionName::Capitals:
      return _capitals;
    case OptionName::Number:
      return _numbers;
    default:
      return _symbols;
    }
  }

  void save() const;
  void read();

private:
  const std::string _filename;

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
