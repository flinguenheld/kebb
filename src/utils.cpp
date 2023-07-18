#include "utils.h"

// clang-format off
std::string kebb::keycode_to_string(uint16_t val) {

  switch (val) {

    case 10:       return "a";
    case 11:       return "b";
    case 12:       return "c";
    case 13:       return "d";
    case 14:       return "e";
    case 15:       return "f";
    case 16:       return "g";
    case 17:       return "h";
    case 18:       return "i";
    case 19:       return "j";
    case 20:       return "k";
    case 21:       return "l";
    case 22:       return "m";
    case 23:       return "n";
    case 24:       return "o";
    case 25:       return "p";
    case 26:       return "q";
    case 27:       return "r";
    case 28:       return "s";
    case 29:       return "t";
    case 30:       return "u";
    case 31:       return "v";
    case 32:       return "w";
    case 33:       return "x";
    case 34:       return "y";
    case 35:       return "z";

    case 100:      return "A";
    case 101:      return "B";
    case 102:      return "C";
    case 103:      return "D";
    case 104:      return "E";
    case 105:      return "F";
    case 106:      return "G";
    case 107:      return "H";
    case 108:      return "I";
    case 109:      return "J";
    case 110:      return "K";
    case 111:      return "L";
    case 112:      return "M";
    case 113:      return "N";
    case 114:      return "O";
    case 115:      return "P";
    case 116:      return "Q";
    case 117:      return "R";
    case 118:      return "S";
    case 119:      return "T";
    case 120:      return "U";
    case 121:      return "V";
    case 122:      return "W";
    case 123:      return "X";
    case 124:      return "Y";
    case 125:      return "Z";

    case 500:      return "0";
    case 501:      return "1";
    case 502:      return "2";
    case 503:      return "3";
    case 504:      return "4";
    case 505:      return "5";
    case 506:      return "6";
    case 507:      return "7";
    case 508:      return "8";
    case 509:      return "9";

    case 1000:     return "!";
    case 1001:     return "'";
    case 1002:     return "#";
    case 1003:     return "%";
    case 1004:     return "$";
    case 1005:     return "&";
    case 1006:     return "\"";
    case 1007:     return "(";
    case 1008:     return ")";
    case 1009:     return "`";
    case 1010:     return "*";
    case 1011:     return "+";
    case 1012:     return ",";
    case 1013:     return "-";
    case 1014:     return ".";
    case 1015:     return "/";
    case 1016:     return ":";
    case 1017:     return ";";
    case 1018:     return "<";
    case 1019:     return "=";
    case 1020:     return ">";
    case 1021:     return "?";
    case 1022:     return "@";
    case 1023:     return "[";
    case 1024:     return "\\";
    case 1025:     return "]";
    case 1026:     return "^";
    case 1027:     return "_";
    case 1028:     return "~";
    case 1029:     return "{";
    case 1030:     return "}";
    case 1031:     return "|";

    default:      return "None";
  }
}


// ----------------------------------------------------------------------------------------------------
// COLORS - Catppucin Mocha ---------------------------------------------------------------------------
SDL_Color kebb::color(kebb::ColorName name) {
  switch (name) {
    case kebb::ColorName::C_Flamingo:
      return {242, 205, 205, 200}; break;
    case kebb::ColorName::C_Pink:
      return {245, 194, 231, 200}; break;
    case kebb::ColorName::C_Mauve:
      return {203, 166, 247, 200}; break;
    case kebb::ColorName::C_Red:
      return {243, 139, 168, 200}; break;
    case kebb::ColorName::C_Maroon:
      return {235, 160, 172, 200}; break;
    case kebb::ColorName::C_Peach:
      return {250, 179, 135, 200}; break;
    case kebb::ColorName::C_Yellow:
      return {249, 226, 175, 200}; break;
    case kebb::ColorName::C_Green:
      return {166, 227, 161, 200}; break;
    case kebb::ColorName::C_Teal:
      return {148, 226, 213, 200}; break;
    case kebb::ColorName::C_Sky:
      return {137, 220, 235, 200}; break;
    case kebb::ColorName::C_Sapphire:
      return {116, 199, 236, 200}; break;
    case kebb::ColorName::C_Blue:
      return {137, 180, 250, 200}; break;
    case kebb::ColorName::C_Lavender:
      return {180, 190, 254, 200}; break;
    case kebb::ColorName::C_Text:
      return {205, 214, 244, 200}; break;
    case kebb::ColorName::C_Overlay2:
      return {147, 153, 178, 200}; break;
    case kebb::ColorName::C_Overlay1:
      return {127, 132, 156, 200}; break;
    case kebb::ColorName::C_Overlay0:
      return {108, 112, 134, 200}; break;
    case kebb::ColorName::C_Surface2:
      return {88, 91, 112, 200}; break;
    case kebb::ColorName::C_Surface1:
      return {69, 71, 90, 200}; break;
    case kebb::ColorName::C_Surface0:
      return {49, 50, 68, 200}; break;
    default:
    // case kebb::ColorName::C_Base:
      return {30, 30, 46, 200}; break;
  }
}
