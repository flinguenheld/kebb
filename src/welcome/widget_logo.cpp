#include "widget_logo.h"
#include "SDL_rect.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <iostream>
#include <vector>

WidgetLogo::WidgetLogo(point position, boxsize size)
    : WidgetBase(position, size), _nb_cases(10), _nb_lines(4), random_case(0, _nb_cases - 1),
      random_line(0, _nb_lines - 1) {

  _border_thickness = size.w / 50;

  _key_size.w = (size.w - (2 * _border_thickness)) / (_nb_cases + 2);
  _key_size.h = (size.h - (2 * _border_thickness)) / (_nb_lines + 2);

  _space_w = (size.w - (2 * _border_thickness) - (_key_size.w * _nb_cases)) / (_nb_cases + 1);
  _space_h = (size.h - (2 * _border_thickness) - (_key_size.h * _nb_lines)) / (_nb_lines + 1);

  std::cout << "key size w: " << _key_size.w << std::endl;
  std::cout << "space w" << _space_w << std::endl;

  for (uint8_t i = 0; i < _nb_lines; ++i) {
    std::vector<bool> v;
    for (uint8_t j = 0; j < _nb_cases; ++j) {
      v.emplace_back(true);
    }
    _tab.emplace_back(v);
  }

  std::cout << "message" << position.x << "-" << position.y << std::endl;
}
WidgetLogo::~WidgetLogo() {}

void WidgetLogo::update() {

  const auto l = random_line(_engine);
  const auto c = random_case(_engine);

  std::cout << "l" << l << std::endl;
  std::cout << "c" << c << std::endl;
  _tab[l][c] = !_tab[l][c];
}

void WidgetLogo::render(SDL_Renderer *renderer, TTF_Font *font) const { // FIX: remove font

  // ------------------------------------------------------------------------
  // Border -----------------------------------------------------------------
  SDL_Rect border_background;
  border_background.w = _size.w;
  border_background.h = _size.h;
  border_background.x = _position.x;
  border_background.y = _position.y;

  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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

      if (c) {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xCC, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &keys);
      }
      keys.x += _key_size.w + _space_w;
    }
    keys.y += _key_size.h + _space_h;
    keys.x = _position.x + _border_thickness + _space_w;
  }
}
