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
    : WidgetBase(position, size), _nb_cases(12), _nb_lines(4), random_case(0, _nb_cases - 1),
      random_line(0, _nb_lines - 1), _continue(true) {

  _border_thickness = size.w / 50;

  _key_size.w = (size.w - (2 * _border_thickness)) / (_nb_cases + 2);
  _key_size.h = (size.h - (2 * _border_thickness)) / (_nb_lines + 2);

  _space_w = (size.w - (2 * _border_thickness) - (_key_size.w * _nb_cases)) / (_nb_cases + 1);
  _space_h = (size.h - (2 * _border_thickness) - (_key_size.h * _nb_lines)) / (_nb_lines + 1);

  // Fill
  for (int16_t i = 0; i < _nb_lines; ++i) {
    std::vector<int16_t> v;
    for (int16_t j = 0; j < _nb_cases; ++j) {
      v.emplace_back(0);
    }
    _tab.emplace_back(v);
  }

  // TODO: Add a random cool choice ?

  // Set the first picture
  int16_t j = 3;
  for (int16_t i = 0; i < 4; ++i) {
    fill(i, j);
    --j;
  }
}
WidgetLogo::~WidgetLogo() {}

void WidgetLogo::fill(uint8_t line, uint8_t column_start) {

  uint8_t nb = 1;
  for (uint8_t i = column_start; i < column_start + 3; ++i) {
    _tab[line][i] = nb;
    ++nb;
  }
}

void WidgetLogo::update() {

  while (_continue) {

    for (uint8_t i = 0; i < _tab.size(); ++i) {
      auto val = _tab[i].back();
      _tab[i].pop_back();
      _tab[i].emplace(_tab[i].begin(), val);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
void WidgetLogo::stop() { _continue = false; }

void WidgetLogo::render(SDL_Renderer *renderer, TTF_Font *font) const { // FIX: remove font

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
        SDL_SetRenderDrawColor(renderer, 250, 179, 135, 150); // Peach
        break;
      case 2:
        SDL_SetRenderDrawColor(renderer, 250, 179, 135, 100); // Peach
        break;
      case 1:
        SDL_SetRenderDrawColor(renderer, 250, 179, 135, 50); // Peach
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
