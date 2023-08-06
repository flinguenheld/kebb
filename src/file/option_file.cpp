#include "option_file.h"

OptionFile::OptionFile()
    : File("options.kebb"), _resolution("480-20"), _layout("US"), _nb_targets(5), _countdown(30), _speed(20),
      _survival_diffilculty(2), _last_mod(2), _letters(true), _capitals(false), _numbers(true),
      _symbols(false), _french_extras(false), _french_extra_caps(false) {

  std::ifstream f(_filename); // First launch
  if (!f.good())
    save();
}

void OptionFile::save() const {
  std::ofstream ostrm(_filename);
  ostrm << _resolution << '\n'
        << _layout << '\n'
        << _nb_targets << '\n'
        << _countdown << '\n'
        << _speed << '\n'
        << _survival_diffilculty << '\n'
        << _last_mod << '\n'
        << _letters << '\n'
        << _capitals << '\n'
        << _numbers << '\n'
        << _symbols << '\n'
        << _french_extras << '\n'
        << _french_extra_caps;
}

void OptionFile::read() {
  std::ifstream istrm(_filename);
  istrm >> _resolution >> _layout >> _nb_targets >> _countdown >> _speed >> _survival_diffilculty >>
      _last_mod >> _letters >> _capitals >> _numbers >> _symbols >> _french_extras >> _french_extra_caps;
}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
std::string OptionFile::get_string(OptionName name) const {
  switch (name) {
  case OptionName::Resolution:
    return _resolution;
  case OptionName::Layout:
    return _layout;
  default:
    std::cout << "Wrong get option: not a string" << std::endl;
    return std::string();
  }
}
uint16_t OptionFile::get_uint(OptionName name) const {
  switch (name) {
  case OptionName::Targets:
    return _nb_targets;
  case OptionName::Countdown:
    return _countdown;
  case OptionName::Speed:
    return _speed;
  case OptionName::SurvivalDifficulty:
    return _survival_diffilculty;
  case OptionName::LastMod:
    return _last_mod;
  default:
    std::cout << "Wrong get option: not an uint" << std::endl;
    return 0;
  }
}
bool OptionFile::get_bool(OptionName name) const {
  switch (name) {
  case OptionName::Letters:
    return _letters;
  case OptionName::Capitals:
    return _capitals;
  case OptionName::Numbers:
    return _numbers;
  case OptionName::Symbols:
    return _symbols;
  case OptionName::FrenchExtras:
    return _french_extras;
  case OptionName::FrenchExtraCaps:
    return _french_extra_caps;
  default:
    std::cout << "Wrong get option: not a bool" << std::endl;
    return false;
  }
}

void OptionFile::set(OptionName name, const std::string val) {
  switch (name) {
  case OptionName::Resolution:
    _resolution = val;
    break;
  case OptionName::Layout:
    _layout = val;
    break;
  default:
    std::cout << "Wrong set option: not a string" << std::endl;
    break;
  }
}
void OptionFile::set(OptionName name, uint16_t val) {
  switch (name) {
  case OptionName::Targets:
    _nb_targets = val;
    break;
  case OptionName::Countdown:
    _countdown = val;
    break;
  case OptionName::Speed:
    _speed = val;
    break;
  case OptionName::SurvivalDifficulty:
    _survival_diffilculty = val;
    break;
  case OptionName::LastMod:
    _last_mod = val;
    break;
  default:
    std::cout << "Wrong set option: not an uint" << std::endl;
    break;
  }
}
void OptionFile::set(OptionName name, bool val) {
  switch (name) {
  case OptionName::Letters:
    _letters = val;
    break;
  case OptionName::Capitals:
    _capitals = val;
    break;
  case OptionName::Numbers:
    _numbers = val;
    break;
  case OptionName::Symbols:
    _symbols = val;
    break;
  case OptionName::FrenchExtras:
    _french_extras = val;
    break;
  case OptionName::FrenchExtraCaps:
    _french_extra_caps = val;
    break;
  default:
    std::cout << "Wrong set option: not a bool " << uint16_t(name) << std::endl;
    break;
  }
}
