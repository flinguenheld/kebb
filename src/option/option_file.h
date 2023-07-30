#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include <fstream>
#include <iostream>
#include <string>

enum class OptionName {
  Resolution,
  Layout,
  Targets,
  Countdown,
  Speed,
  SurvivalDifficulty,
  Letters,
  Capitals,
  Numbers,
  Symbols,
  FrenchExtras,
  FrenchExtraCaps,
};

/*
 * Allows to read and save the option file.
 * All entries are saved in string format.
 */
class OptionFile {
public:
  OptionFile();

  void save() const;
  void read();

  void set(OptionName type, const std::string &val);
  std::string get(OptionName type);

private:
  std::string _filename;

  std::string _resolution;
  std::string _layout;

  std::string _nb_targets;
  std::string _countdown;
  std::string _speed;

  std::string _survival_diffilculty;

  std::string _letters;
  std::string _capitals;
  std::string _numbers;
  std::string _symbols;
  std::string _french_extras;
  std::string _french_extra_caps;
};

#endif // !OPTION_FILE_H
