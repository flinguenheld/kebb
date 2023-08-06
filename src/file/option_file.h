#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include "file.h"

enum class OptionName {
  Resolution,
  Layout,
  Targets,
  Countdown,
  Speed,
  SurvivalDifficulty,
  LastMod,
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
class OptionFile : public File {
public:
  OptionFile();

  void save() const;
  void read();

  void set(OptionName type, const std::string &val);
  std::string get(OptionName type) const;

private:
  std::string _resolution;
  std::string _layout;

  std::string _nb_targets;
  std::string _countdown;
  std::string _speed;

  std::string _survival_diffilculty;

  std::string _last_mod;

  std::string _letters;
  std::string _capitals;
  std::string _numbers;
  std::string _symbols;
  std::string _french_extras;
  std::string _french_extra_caps;
};

#endif // !OPTION_FILE_H
