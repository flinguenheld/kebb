#include "utils.h"

std::string kebb::adapt_string_length(std::string &&text, uint8_t text_length, char c) {
  while (text.length() < text_length)
    text.insert(0, 1, c);

  return std::move(text); // NOTE: Is move here farfetch ?
}

std::string kebb::speed(uint waiting_time) {

  switch (waiting_time) {
  case 30:
    return "1";
  case 28:
    return "2";
  case 26:
    return "3";
  case 24:
    return "4";
  case 22:
    return "5";
  case 20:
    return "6";
  case 18:
    return "7";
  case 16:
    return "8";
  case 14:
    return "9";
  case 12:
    return "10";
  case 10:
    return "11";
  case 8:
    return "12";
  case 6:
    return "13";
  case 4:
    return "14";
  case 2:
    return "15";
  default:
    return "16";
  }
}

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

    // French extras
    case 2000:     return "é";
      case 2001:     return "à";
      case 2002:     return "è";
      case 2003:     return "ù";
    case 2004:     return "â";
    case 2005:     return "ê";
    case 2006:     return "î";
    case 2007:     return "ô";
    case 2008:     return "û";
      case 2009:     return "ï";
      case 2010:     return "ë";
      case 2011:     return "ü";
    case 2012:     return "ç";
      case 2013:    return "€";
    case 2014:     return "æ";
    case 2015:     return "œ";

    case 2100:     return "É";
      case 2101:     return "À";
      case 2102:     return "È";
      case 2103:     return "Ù";
    case 2104:     return "Â";
    case 2105:     return "Ê";
    case 2106:     return "Î";
    case 2107:     return "Ô";
    case 2108:     return "Û";
      case 2109:     return "Ï";
      case 2110:     return "Ë";
      case 2111:     return "Ü";
    case 2112:     return "Ç";
      case 2113:     return "Æ";
      case 2114:     return "Œ";

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
