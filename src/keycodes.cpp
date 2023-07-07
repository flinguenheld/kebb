#include "keycodes.h"

// clang-format off
std::string keycode_to_string(uint16_t val) {

  switch (val) {

    case 10:      return "a";
    case 11:      return "b";
    case 12:      return "c";
    case 13:      return "d";
    case 14:      return "e";
    case 15:      return "f";
    case 16:      return "g";
    case 17:      return "h";
    case 18:      return "i";
    case 19:      return "j";
    case 20:      return "k";
    case 21:      return "l";
    case 22:      return "m";
    case 23:      return "n";
    case 24:      return "o";
    case 25:      return "p";
    case 26:      return "q";
    case 27:      return "r";
    case 28:      return "s";
    case 29:      return "t";
    case 30:      return "u";
    case 31:      return "v";
    case 32:      return "w";
    case 33:      return "x";
    case 34:      return "y";
    case 35:      return "z";

    default:      return "None";
  }
}
