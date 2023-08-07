/* Regroup general structs and variables. */

#ifndef UTILS_H
#define UTILS_H

#include "SDL_pixels.h"
#include <math.h>
#include <string>

// clang-format off
namespace kebb {

  // ----------------------------------------------------------------------------------------------------
  // GEOMETRY -------------------------------------------------------------------------------------------
  struct point {
    uint16_t x;
    uint16_t y;

    point() : x(0), y(0){};
    point(uint16_t x, uint16_t y) : x(x), y(y){};
    float distance(const kebb::point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
  };

  struct boxsize {
    uint16_t w;
    uint16_t h;

    kebb::boxsize scale(float s) const {
      return kebb::boxsize{static_cast<uint16_t>(w * s), static_cast<uint16_t>(h * s)};
    }
    void set_scale(float s) {
      w = w * s;
      h = h * s;
    };
  };

  /*
   * Allow to make a string longer with the char 'c'.
   * Useful to align text.
   */
  std::string adapt_string_length(std::string &&text, uint8_t text_length, char c = ' ');

  // ----------------------------------------------------------------------------------------------------
  // GAME MODS ------------------------------------------------------------------------------------------
  enum class GameMod {
    M_Survival = 10,
    M_Timer = 11,
  };

  // ----------------------------------------------------------------------------------------------------
  // GAME STATUS ----------------------------------------------------------------------------------------
  enum class GameStatus {
    S_Win = 10,
    S_Loose = 11,
    S_TimeUp = 12,
    S_Quit = 13,
  };

  // ----------------------------------------------------------------------------------------------------
  // WINDOWNAME (used to navigate) ----------------------------------------------------------------------
  enum class WindowName {
    W_None,
    W_Quit,

    W_About,
    W_GameTimer,
    W_GameSurvival,
    W_Option,
    W_GameOver,
    W_Welcome,
    W_WelcomeTimer,
    W_WelcomeSurvival,
  };

  // ----------------------------------------------------------------------------------------------------
  // KEYCODES -------------------------------------------------------------------------------------------
  std::string keycode_to_string(uint16_t val);

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
