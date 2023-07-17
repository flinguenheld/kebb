#include "option_file.h"

OptionFile::OptionFile()
    : _filename("options.kebb"), _layout(""), _nb_targets("1"), _countdown("1"), _speed("1"), _letters("1"),
      _capitals("1"), _numbers("1"), _symbols("1") {}

void OptionFile::save() const {
  std::ofstream ostrm(_filename);
  ostrm << _resolution << '\n'
        << _layout << '\n'
        << _nb_targets << '\n'
        << _countdown << '\n'
        << _speed << '\n'
        << _letters << '\n'
        << _capitals << '\n'
        << _numbers << '\n'
        << _symbols;
}

void OptionFile::read() {
  std::ifstream istrm(_filename);
  istrm >> _resolution >> _layout >> _nb_targets >> _countdown >> _speed >> _letters >> _capitals >>
      _numbers >> _symbols;
}

// ----------------------------------------------------------------------------------------------------
// ASSESSORS ------------------------------------------------------------------------------------------
void OptionFile::set(OptionName type, const std::string &val) {
  switch (type) {
  case OptionName::Resolution:
    _resolution = val;
    break;
  case OptionName::Layout:
    _layout = val;
    break;
  case OptionName::Targets:
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
  case OptionName::Numbers:
    _numbers = val;
    break;
  default:
    _symbols = val;
  }
}

std::string OptionFile::get(OptionName name) {

  switch (name) {
  case OptionName::Resolution:
    return _resolution;
  case OptionName::Layout:
    return _layout;
  case OptionName::Targets:
    return _nb_targets;
  case OptionName::Countdown:
    return _countdown;
  case OptionName::Speed:
    return _speed;
  case OptionName::Letters:
    return _letters;
  case OptionName::Capitals:
    return _capitals;
  case OptionName::Numbers:
    return _numbers;
  default:
    return _symbols;
  }
}
