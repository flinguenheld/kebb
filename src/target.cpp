#include "target.h"
#include <iostream>
#include <iterator>

Target::Target(int x, int y, int radius)
    : _txt(), _font(nullptr), _center(x, y), _center_txt(x, y), _position(x, y), _radius(radius), _alpha(1) {}

void Target::update() {

  // TODO: Add severals moving styles
  _position.x++;
  _position.y--;

  _center_txt.x = _position.x + _w / 2;
  _center_txt.y = _position.y + _h / 2;

  int distance = _center.distance(_center_txt);

  // TODO: Add colour change to turn in red ?
  // Fade --
  if (distance <= _radius * 0.2)
    _alpha += 5;
  else if (distance >= (_radius * 0.8) && distance <= _radius)
    _alpha -= 5;
  else if (distance > _radius) {
    init();
    distance = 0;
    _alpha = 1;
  }

  _alpha = _alpha > 200 ? 200 : (_alpha < 1 ? 1 : _alpha);

  _color = {255, 255, 255, static_cast<Uint8>(_alpha)};
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

  _color = {0x1E, 0x5E, 0x15, 0xFF};

  _position.x = _center.x - _w / 2;
  _position.y = _center.y - _h / 2;
}
