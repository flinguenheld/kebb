/* Regroup general structs and the keycode list. */

#ifndef UTILS_H
#define UTILS_H

#include "SDL_pixels.h"
#include <cstdint>
#include <math.h>
#include <string>

struct point {
  uint16_t x;
  uint16_t y;

  point() : x(0), y(0){};
  point(uint16_t x, uint16_t y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

struct boxsize {
  uint16_t w;
  uint16_t h;

  boxsize scale(float s) const { return boxsize{static_cast<uint16_t>(w * s), static_cast<uint16_t>(h * s)}; }
  void set_scale(float s) {
    w = w * s;
    h = h * s;
  };
};

// ----------------------------------------------------------------------------------------------------
// WINDOWNAME (used to navigate) ----------------------------------------------------------------------
enum class WindowName {
  W_None,
  W_Quit,

  W_About,
  W_Game,
  W_Option,
  W_Pause,
  W_Welcome,
};

// ----------------------------------------------------------------------------------------------------
// KEYCODES -------------------------------------------------------------------------------------------
std::string keycode_to_string(uint16_t val);

namespace kebb {
// ----------------------------------------------------------------------------------------------------
// COLORS - Catppucin Mocha ---------------------------------------------------------------------------
enum class ColorName {
  C_Flamingo,
  C_Pink,
  C_Mauve,
  C_Red,
  C_Maroon,
  C_Peach,
  C_Yellow,
  C_Green,
  C_Teal,
  C_Sky,
  C_Sapphire,
  C_Blue,
  C_Lavender,
  C_Text,
  C_Overlay2,
  C_Overlay1,
  C_Overlay0,
  C_Surface2,
  C_Surface1,
  C_Surface0,
  C_Base,
};

SDL_Color color(ColorName name);
} // namespace kebb
#endif // !UTILS_H
