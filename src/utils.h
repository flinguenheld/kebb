#ifndef UTILS_H
#define UTILS_H

/*
 * Regroup general structs and the keycode list.
 */

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
  W_Welcome,
  W_Game,
  W_Pause,
  W_Option,
  W_Quit,
};

// ----------------------------------------------------------------------------------------------------
// KEYCODES -------------------------------------------------------------------------------------------
std::string keycode_to_string(uint16_t val);

#endif // !UTILS_H
