#include "option_file.h"

OptionFile::OptionFile()
    : _filename("options.kebb"), _layout(2), _nb_targets(1), _countdown(1), _speed(5), _letters(true),
      _capitals(false), _numbers(false), _symbols(false) {}

void OptionFile::save() const {
  std::ofstream ostrm(_filename);
  ostrm << _resolution << ' ' << _layout << ' ' << _nb_targets << ' ' << _countdown << ' ' << _speed << ' '
        << _letters << ' ' << _capitals << ' ' << _numbers << ' ' << _symbols;
}

void OptionFile::read() {
  std::ifstream istrm(_filename);
  istrm >> _resolution >> _layout >> _nb_targets >> _countdown >> _speed >> _letters >> _capitals >>
      _numbers >> _symbols;
}

// ----------------------------------------------------------------------------------------------------
// ASSESSORS ------------------------------------------------------------------------------------------

void OptionFile::set(OptionName type, int16_t val) {
  switch (type) {
  case OptionName::Resolution:
    _resolution = val;
    break;
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

int16_t OptionFile::get(OptionName type) {
  switch (type) {
  case OptionName::Resolution:
    return _resolution;
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
