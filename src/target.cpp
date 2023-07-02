#include "target.h"

Target::Target(int h_screen, int w_screen)
    : _txt(), _font(nullptr), _w_screen(w_screen), _h_screen(h_screen) {}

void Target::update() {
  _x++;
  _y++;

  std::cout << "x: " << _x << "  screen: " << _w_screen << std::endl;
  std::cout << "y: " << _y << std::endl;

  int x_center = _x + _w / 2;
  int y_center = _y + _h / 2;

  if (x_center <= 0 || x_center >= _w_screen || y_center <= 0 || y_center >= _h_screen)
    init();

  _color = {0x1E, 0x5E, 0x15, 0xFF};
}

void Target::setText(std::string txt, TTF_Font *font) {

  _font = font;
  _txt = txt;

  std::cout << TTF_SizeText(_font, char_ptr(), &_w, &_h) << "\n";

  _x = _w_screen / 2 + _w / 2;
  _y = _h_screen / 2 + _h / 2;
}

const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

int Target::x() const { return _x; }
int Target::y() const { return _y; }

int Target::h() const { return _h; }
int Target::w() const { return _w; }

void Target::init() {

  _x = _w_screen / 2 - _w / 2;
  _y = _h_screen / 2 - _h / 2;
}
