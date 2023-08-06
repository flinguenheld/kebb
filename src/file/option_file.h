#ifndef OPTION_FILE_H
#define OPTION_FILE_H

#include "file.h"
#include <cstdint>

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
 */
class OptionFile : public File {
public:
  OptionFile();

  void save() const;
  void read();

  std::string get_string(OptionName name) const;
  uint16_t get_uint(OptionName name) const;
  bool get_bool(OptionName name) const;

  void set(OptionName name, const std::string val);
  void set(OptionName name, uint16_t val);
  void set(OptionName name, bool val);

private:
  std::string _resolution;
  std::string _layout;

  uint16_t _nb_targets;
  uint16_t _countdown;
  uint16_t _speed;

  uint16_t _survival_diffilculty;

  uint16_t _last_mod;

  bool _letters;
  bool _capitals;
  bool _numbers;
  bool _symbols;
  bool _french_extras;
  bool _french_extra_caps;
};

#endif // !OPTION_FILE_H
