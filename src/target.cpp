#include "target.h"

Target::Target(int h_screen, int w_screen) : _txt(), _font(nullptr), _w_area(w_screen), _h_aera(h_screen) {

  _center_area.x = _w_area / 2;
  _center_area.y = _h_aera / 2;
}

void Target::update() {
  _position.x++;
  _position.y++;

  _center_txt.x = _position.x + _w / 2;
  _center_txt.y = _position.y + _h / 2;

  if (_center_txt.x <= 0 || _center_txt.x >= _w_area || _center_txt.y <= 0 || _center_txt.y >= _h_aera)
    init();

  std::cout << _position.distance(_center_area) << std::endl;
  int d = _position.distance(_center_area);
  if (d < _w_area / 5)
    _color = {0x13, 0x2B, 0x55, 0x55};
  else if (d < _w_area / 4)
    _color = {0x13, 0x2B, 0x22, 0xFF};
  else if (d < _w_area / 3)
    _color = {0x13, 0x5A, 0x55, 0xFF};
  else if (d < _w_area / 2)
    _color = {0x13, 0x5A, 0x55, 0xFF};
  else
    _color = {0x13, 0x2B, 0xaa, 0xFF};
}

void Target::setText(std::string txt, TTF_Font *font) {

  _font = font;
  _txt = txt;

  std::cout << TTF_SizeText(_font, char_ptr(), &_w, &_h) << "\n";

  _position.x = _w_area / 2 + _w / 2;
  _position.y = _h_aera / 2 + _h / 2;
}

const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

point Target::position() const { return _position; };

int Target::h() const { return _h; }
int Target::w() const { return _w; }

void Target::init() {

  _color = {0x1E, 0x5E, 0x15, 0xFF};
  _position.x = _w_area / 2 - _w / 2;
  _position.y = _h_aera / 2 - _h / 2;
}
