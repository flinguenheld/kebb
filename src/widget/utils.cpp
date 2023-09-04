#include "utils.h"

std::string widget::adapt_string_length(std::string &&text, uint8_t text_length, char c) {
  while (text.length() < text_length)
    text.insert(0, 1, c);

  return text;
}

// clang-format off
// ----------------------------------------------------------------------------------------------------
// COLORS - Catppucin Mocha ---------------------------------------------------------------------------
SDL_Color widget::color(widget::ColorName name) {
  switch (name) {
    case widget::ColorName::C_Flamingo:
      return {242, 205, 205, 200}; break;
    case widget::ColorName::C_Pink:
      return {245, 194, 231, 200}; break;
    case widget::ColorName::C_Mauve:
      return {203, 166, 247, 200}; break;
    case widget::ColorName::C_Red:
      return {243, 139, 168, 200}; break;
    case widget::ColorName::C_Maroon:
      return {235, 160, 172, 200}; break;
    case widget::ColorName::C_Peach:
      return {250, 179, 135, 200}; break;
    case widget::ColorName::C_Yellow:
      return {249, 226, 175, 200}; break;
    case widget::ColorName::C_Green:
      return {166, 227, 161, 200}; break;
    case widget::ColorName::C_Teal:
      return {148, 226, 213, 200}; break;
    case widget::ColorName::C_Sky:
      return {137, 220, 235, 200}; break;
    case widget::ColorName::C_Sapphire:
      return {116, 199, 236, 200}; break;
    case widget::ColorName::C_Blue:
      return {137, 180, 250, 200}; break;
    case widget::ColorName::C_Lavender:
      return {180, 190, 254, 200}; break;
    case widget::ColorName::C_Text:
      return {205, 214, 244, 200}; break;
    case widget::ColorName::C_Overlay2:
      return {147, 153, 178, 200}; break;
    case widget::ColorName::C_Overlay1:
      return {127, 132, 156, 200}; break;
    case widget::ColorName::C_Overlay0:
      return {108, 112, 134, 200}; break;
    case widget::ColorName::C_Surface2:
      return {88, 91, 112, 200}; break;
    case widget::ColorName::C_Surface1:
      return {69, 71, 90, 200}; break;
    case widget::ColorName::C_Surface0:
      return {49, 50, 68, 200}; break;
    default:
    // case widget::ColorName::C_Base:
      return {30, 30, 46, 200}; break;
  }
}
