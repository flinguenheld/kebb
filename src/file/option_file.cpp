#include "option_file.h"

OptionFile::OptionFile() : File("options.kebb") {

  std::ifstream f(_filename); // First launch
  if (!f.good())
    save();

  read();
}
OptionFile::~OptionFile() { save(); }

void OptionFile::save() const {
  std::ofstream ostrm(_filename);
  ostrm << _options.resolution << '\n'
        << _options.layout << '\n'
        << _options.timer_countdown << '\n'
        << _options.timer_nb_targets << '\n'
        << _options.timer_speed << '\n'
        << _options.survival_nb_targets << '\n'
        << _options.survival_speed << '\n'
        << _options.last_mod << '\n'
        << _options.letters << '\n'
        << _options.capitals << '\n'
        << _options.numbers << '\n'
        << _options.symbols << '\n'
        << _options.french_extras << '\n'
        << _options.french_extra_caps;
}

void OptionFile::read() {
  std::ifstream istrm(_filename);
  istrm >> _options.resolution >> _options.layout >> _options.timer_countdown >> _options.timer_nb_targets >>
      _options.timer_speed >> _options.survival_nb_targets >> _options.survival_speed >> _options.last_mod >>
      _options.letters >> _options.capitals >> _options.numbers >> _options.symbols >>
      _options.french_extras >> _options.french_extra_caps;
}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
const Options &OptionFile::get() const { return _options; }
Options &OptionFile::set() { return _options; }
