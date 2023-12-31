#include "widget_logo.h"

WidgetLogo::WidgetLogo(widget::point position, widget::boxsize size)
    : WidgetBase(position, size), _nb_colums(12), _nb_lines(4), _engine(_seed()), _continue(true) {

  _color_border = widget::color(widget::ColorName::C_Surface1);
  _color_key = widget::color(widget::ColorName::C_Surface0);

  // ------------------------------------------------------------------------
  // Geometry ---------------------------------------------------------------
  _border_thickness = size.w / 50;

  _key_size.w = (size.w - (2 * _border_thickness)) / (_nb_colums + 2);
  _key_size.h = (size.h - (2 * _border_thickness)) / (_nb_lines + 2);

  _space_w = (size.w - (2 * _border_thickness) - (_key_size.w * _nb_colums)) / (_nb_colums + 1);
  _space_h = (size.h - (2 * _border_thickness) - (_key_size.h * _nb_lines)) / (_nb_lines + 1);

  // ------------------------------------------------------------------------
  // Table of values --------------------------------------------------------
  for (int16_t i = 0; i < _nb_lines; ++i) {
    std::vector<uint16_t> v;
    for (int16_t j = 0; j < _nb_colums; ++j) {
      v.emplace_back(0);
    }
    _tab.emplace_back(v);
  }

  // ------------------------------------------------------------------------
  // Randomise --------------------------------------------------------------
  std::uniform_int_distribution<uint16_t> _random_animation(0, 2); // Which animation ?
  _type_animation = _random_animation(_engine);

  std::uniform_int_distribution<uint16_t> _random_color(0, 13); // Which color ?
  switch (_random_color(_engine)) {
    // clang-format off
    case 0:  _color_current = widget::color(widget::ColorName::C_Flamingo); break;
    case 1:  _color_current = widget::color(widget::ColorName::C_Pink); break;
    case 2:  _color_current = widget::color(widget::ColorName::C_Mauve); break;
    case 3:  _color_current = widget::color(widget::ColorName::C_Red); break;
    case 4:  _color_current = widget::color(widget::ColorName::C_Maroon); break;
    case 5:  _color_current = widget::color(widget::ColorName::C_Peach); break;
    case 6:  _color_current = widget::color(widget::ColorName::C_Yellow); break;
    case 7:  _color_current = widget::color(widget::ColorName::C_Green); break;
    case 8:  _color_current = widget::color(widget::ColorName::C_Teal); break;
    case 9:  _color_current = widget::color(widget::ColorName::C_Sky); break;
    case 10: _color_current = widget::color(widget::ColorName::C_Sapphire); break;
    case 11: _color_current = widget::color(widget::ColorName::C_Blue); break;
    case 12: _color_current = widget::color(widget::ColorName::C_Lavender); break;
    default: _color_current = widget::color(widget::ColorName::C_Text); break;
    // clang-format on
  }

  // ------------------------------------------------------------------------
  // Filling table according to the animation -------------------------------
  if (_type_animation == 0) {

    std::uniform_int_distribution<uint16_t> random_start(0, _nb_colums - 4);

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
      std::uniform_int_distribution<uint16_t> random_case(0, _nb_colums - 1);

      if (random_case(_engine) % 2 == 0) {
        auto l = random_line(_engine);
        auto c = random_case(_engine);

        if (_tab[l][c] == 0) {
          _tab[l][c] = 4;
        }
      }

      for (int16_t i = 0; i < _nb_lines; ++i) {
        for (int16_t j = 0; j < _nb_colums; ++j) {
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

  SDL_SetRenderDrawColor(renderer, _color_border.r, _color_border.g, _color_border.b, 200);
  SDL_RenderFillRect(renderer, &border_background);

  // ------------------------------------------------------------------------
  // Background -------------------------------------------------------------
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
        SDL_SetRenderDrawColor(renderer, _color_current.r, _color_current.g, _color_current.b, 150);
        break;
      case 2:
        SDL_SetRenderDrawColor(renderer, _color_current.r, _color_current.g, _color_current.b, 100);
        break;
      case 1:
        SDL_SetRenderDrawColor(renderer, _color_current.r, _color_current.g, _color_current.b, 50);
        break;
      default:
        SDL_SetRenderDrawColor(renderer, _color_key.r, _color_key.g, _color_key.b, 200);
        break;
      }

      SDL_RenderFillRect(renderer, &keys);
      keys.x += _key_size.w + _space_w;
    }
    keys.y += _key_size.h + _space_h;
    keys.x = _position.x + _border_thickness + _space_w;
  }
}
