#include "widget_logo.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <functional>
#include <iostream>
#include <thread>
#include <vector>

WidgetLogo::WidgetLogo(point position, boxsize size)
    : WidgetBase(position, size), _nb_cases(12), _nb_lines(4), _engine(_seed()), _continue(true) {

  // ------------------------------------------------------------------------
  // Geometry ---------------------------------------------------------------
  _border_thickness = size.w / 50;

  _key_size.w = (size.w - (2 * _border_thickness)) / (_nb_cases + 2);
  _key_size.h = (size.h - (2 * _border_thickness)) / (_nb_lines + 2);

  _space_w = (size.w - (2 * _border_thickness) - (_key_size.w * _nb_cases)) / (_nb_cases + 1);
  _space_h = (size.h - (2 * _border_thickness) - (_key_size.h * _nb_lines)) / (_nb_lines + 1);

  // ------------------------------------------------------------------------
  // Table of values --------------------------------------------------------
  for (int16_t i = 0; i < _nb_lines; ++i) {
    std::vector<uint16_t> v;
    for (int16_t j = 0; j < _nb_cases; ++j) {
      v.emplace_back(0);
    }
    _tab.emplace_back(v);
  }

  // ------------------------------------------------------------------------
  // Randomise --------------------------------------------------------------
  std::uniform_int_distribution<uint16_t> _random_animation(0, 2); // Which animation ?
  _type_animation = _random_animation(_engine);

  std::uniform_int_distribution<uint16_t> _random_color(0, 5); // Which color ? - Catppuccin Mocha
  switch (_random_color(_engine)) {
  case 0: // Mauve
    _r = 203;
    _g = 166;
    _b = 247;
    break;
  case 1: // Peach
    _r = 250;
    _g = 179;
    _b = 135;
    break;
  case 2: // Green
    _r = 166;
    _g = 227;
    _b = 161;
    break;
  case 3: // Sky
    _r = 137;
    _g = 220;
    _b = 235;
    break;
  case 4: // Blue
    _r = 137;
    _g = 180;
    _b = 250;
    break;
  default: // Text
    _r = 205;
    _g = 214;
    _b = 244;
  }

  // ------------------------------------------------------------------------
  // Filling table according to the animation -------------------------------
  if (_type_animation == 0) {

    std::uniform_int_distribution<uint16_t> random_start(0, _nb_cases - 4);

    for (int16_t i = 0; i < _nb_lines; ++i) {
      uint16_t start = random_start(_engine);
      uint16_t k = 0;
      for (int16_t j = start; j < start + 3; ++j) {
        _tab[i][j] = ++k;
      }
    }

  } else if (_type_animation == 1) {
    _tab[0][5] = 3;
    _tab[0][4] = 2;
    _tab[0][3] = 1;

    _tab[1][4] = 3;
    _tab[1][3] = 2;
    _tab[1][2] = 1;

    _tab[2][3] = 3;
    _tab[2][2] = 2;
    _tab[2][1] = 1;

    _tab[3][2] = 3;
    _tab[3][1] = 2;
    _tab[3][0] = 1;
  }
}
WidgetLogo::~WidgetLogo() {}

// ------------------------------------------------------------------------
// Thread -----------------------------------------------------------------
void WidgetLogo::stop() { _continue = false; }
void WidgetLogo::update() {

  while (_continue) {
    switch (_type_animation) {

    case 0: // Swap cases from left to right
    case 1:
      for (uint8_t i = 0; i < _tab.size(); ++i) {
        auto val = _tab[i].back();
        _tab[i].pop_back();
        _tab[i].emplace(_tab[i].begin(), val);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      break;

    case 2: // Set randomly some cases to 3 and decrease their value up to 0

      std::uniform_int_distribution<uint16_t> random_line(0, _nb_lines - 1);
      std::uniform_int_distribution<uint16_t> random_case(0, _nb_cases - 1);

      if (random_case(_engine) % 2 == 0) {
        auto l = random_line(_engine);
        auto c = random_case(_engine);

        if (_tab[l][c] == 0) {
          _tab[l][c] = 4;
        }
      }

      for (int16_t i = 0; i < _nb_lines; ++i) {
        for (int16_t j = 0; j < _nb_cases; ++j) {
          if (_tab[i][j] != 0)
            _tab[i][j]--;
        }
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(150));
      break;
    }
  }
}

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetLogo::render(SDL_Renderer *renderer) const {

  // ------------------------------------------------------------------------
  // Border -----------------------------------------------------------------
  SDL_Rect border_background;
  border_background.w = _size.w;
  border_background.h = _size.h;
  border_background.x = _position.x;
  border_background.y = _position.y;

  SDL_SetRenderDrawColor(renderer, 69, 71, 90, 200); // Surface1
  SDL_RenderFillRect(renderer, &border_background);
  // ------------------------------------------------------------------------
  // Background -------------------------------------------------------------
  // const uint16_t border_thickness = border.w / 50;

  border_background.w -= _border_thickness * 2;
  border_background.h -= _border_thickness * 2;
  border_background.x += _border_thickness;
  border_background.y += _border_thickness;

  SDL_SetRenderDrawColor(renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderFillRect(renderer, &border_background);

  // ------------------------------------------------------------------------
  // Keyboard ---------------------------------------------------------------
  SDL_Rect keys;
  keys.w = _key_size.w;
  keys.h = _key_size.h;
  keys.x = _position.x + _border_thickness + _space_w;
  keys.y = _position.y + _border_thickness + _space_h;

  for (const auto &v : _tab) {
    for (const auto &c : v) {

      switch (c) {
      case 3:
        SDL_SetRenderDrawColor(renderer, _r, _g, _b, 150);
        break;
      case 2:
        SDL_SetRenderDrawColor(renderer, _r, _g, _b, 100);
        break;
      case 1:
        SDL_SetRenderDrawColor(renderer, _r, _g, _b, 50);
        break;
      default:
        SDL_SetRenderDrawColor(renderer, 49, 50, 68, 200); // Surface0
        break;
      }

      SDL_RenderFillRect(renderer, &keys);
      keys.x += _key_size.w + _space_w;
    }
    keys.y += _key_size.h + _space_h;
    keys.x = _position.x + _border_thickness + _space_w;
  }
}
