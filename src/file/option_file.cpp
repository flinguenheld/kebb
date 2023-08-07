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
        << _options.nb_targets << '\n'
        << _options.countdown << '\n'
        << _options.speed << '\n'
        << _options.survival_difficulty << '\n'
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
  istrm >> _options.resolution >> _options.layout >> _options.nb_targets >> _options.countdown >>
      _options.speed >> _options.survival_difficulty >> _options.last_mod >> _options.letters >>
      _options.capitals >> _options.numbers >> _options.symbols >> _options.french_extras >>
      _options.french_extra_caps;
}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
const Options &OptionFile::get() const { return _options; }
Options &OptionFile::set() { return _options; }
