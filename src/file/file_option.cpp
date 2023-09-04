#include "file_option.h"

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
        << _options.survival_difficulty << '\n'
        << _options.survival_max_fails << '\n'
        << _options.survival_max_misses << '\n'
        << _options.survival_cost_fails << '\n'
        << _options.survival_cost_misses << '\n'
        << _options.survival_next_level << '\n'

        << _options.last_mode << '\n'
        << _options.letters << '\n'
        << _options.capitals << '\n'
        << _options.numbers << '\n'
        << _options.symbols << '\n'
        << _options.symbols_plus << '\n'
        << _options.extras << '\n'
        << _options.extra_caps;
}

void OptionFile::read() { // clang-format off
  std::ifstream istrm(_filename);
  istrm >> _options.resolution
        >> _options.layout

        >> _options.timer_countdown
        >> _options.timer_nb_targets
        >> _options.timer_speed

        >> _options.survival_nb_targets
        >> _options.survival_speed
        >> _options.survival_difficulty
        >> _options.survival_max_fails
        >> _options.survival_max_misses
        >> _options.survival_cost_fails
        >> _options.survival_cost_misses
        >> _options.survival_next_level

        >> _options.last_mode
        >> _options.letters
        >> _options.capitals
        >> _options.numbers
        >> _options.symbols
        >> _options.symbols_plus
        >> _options.extras
        >> _options.extra_caps;
} // clang-format on

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
const Options &OptionFile::get() const { return _options; }
Options &OptionFile::set() { return _options; }
