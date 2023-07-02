#include "target.h"
#include <iostream>

Target::Target(int h_screen, int w_screen) : _txt(), _font(nullptr), _w_area(w_screen), _h_aera(h_screen) {

  _center_area.x = _w_area / 2;
  _center_area.y = _h_aera / 2;
}

void Target::update() {
  _top_left_position.x--;
  _top_left_position.y--;

  _center_txt.x = _top_left_position.x + _w / 2;
  _center_txt.y = _top_left_position.y + _h / 2;

  if (_center_txt.x <= 0 || _center_txt.x >= _w_area || _center_txt.y <= 0 || _center_txt.y >= _h_aera)
    init();

  // TODO: Add colour change to turn in red
  // Fade --
  int rgb = _center_area.distance(_top_left_position) * 2;
  rgb = rgb > 200 ? 200 : (rgb < 1 ? 1 : rgb);

  _color = {255, 255, 255, static_cast<Uint8>(rgb)};
}

void Target::setText(std::string txt, TTF_Font *font) {

  _font = font;
  _txt = txt;

  std::cout << TTF_SizeText(_font, char_ptr(), &_w, &_h) << "\n";

  init();
}

const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

point Target::top_left_position() const { return _top_left_position; };

int Target::h() const { return _h; }
int Target::w() const { return _w; }

void Target::init() {

  _color = {0x1E, 0x5E, 0x15, 0xFF};

  _top_left_position.x = _center_area.x - _w / 2;
  _top_left_position.y = _center_area.y - _h / 2;
}
