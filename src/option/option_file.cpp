#include "option_file.h"

OptionFile::OptionFile()
    : _filename("./options.kebb"), _layout(0), _nb_targets(1), _countdown(1), _speed(5), _letters(true),
      _capitals(false), _numbers(false), _symbols(false) {}

void OptionFile::save() const {

  std::ofstream ostrm(_filename);
  ostrm << _layout << ' ' << _nb_targets << ' ' << _countdown << ' ' << _speed << ' ' << _letters << ' '
        << _capitals << ' ' << _numbers << ' ' << _symbols;
}

void OptionFile::read() {

  std::ifstream istrm(_filename);
  istrm >> _layout >> _nb_targets >> _countdown >> _speed >> _letters >> _capitals >> _numbers >> _symbols;
  std::cout << " read back: " << _layout << " " << _speed << " " << _letters << '\n';
}
