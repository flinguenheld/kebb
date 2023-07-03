#include "target.h"
#include <iostream>
#include <iterator>

Target::Target(int x, int y, int radius)
    : _txt(), _font(nullptr), _center(x, y), _center_txt(x, y), _position(x, y), _radius(radius) {}

void Target::update() {

  // TODO: Add severals moving styles
  _position.x++;
  _position.y--;

  _center_txt.x = _position.x + _w / 2;
  _center_txt.y = _position.y + _h / 2;

  int distance = _center.distance(_center_txt);

  // Fade & colour --
  if (distance <= _radius * 0.2) {

    _color.a = _color.a > 200 ? 200 : _color.a + 5;

  } else if (distance >= (_radius * 0.7) && distance <= _radius) {

    _color.a = _color.a <= 5 ? 5 : _color.a - 5;

    _color.g = _color.g <= 50 ? 50 : _color.g - 15;
    _color.b = _color.b <= 50 ? 50 : _color.b - 15;

  } else if (distance > _radius) {
    init();
    distance = 0;
  }
}

void Target::setText(std::string txt, TTF_Font *font) {

  _font = font;
  _txt = txt;

  TTF_SizeText(_font, char_ptr(), &_w, &_h);
  init();
}

const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

point Target::position() const { return _position; };

int Target::h() const { return _h; }
int Target::w() const { return _w; }

void Target::init() {

  _color = {255, 255, 255, 1};
  _position.x = _center.x - _w / 2;
  _position.y = _center.y - _h / 2;
}
