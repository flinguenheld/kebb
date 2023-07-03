#include "target.h"

Target::Target(int x, int y, int radius)
    : _txt(), _font(nullptr), _center(x, y), _center_txt(x, y), _position(x, y), _radius(radius), _plus_x(1),
      _plus_y(1) {}

/*
 * Move the target and adapt fields according to the distance to the center
 */
void Target::update() {

  // TODO: Add severals moving styles
  _position.x += 5;
  _position.y += -3;

  _center_txt.x = _position.x + _w / 2;
  _center_txt.y = _position.y + _h / 2;

  int distance = _center.distance(_center_txt);

  // Fade & colour --
  if (distance <= _radius * 0.2) {
    _color.a = _color.a > 200 ? 200 : _color.a + 5;

  } else if (distance >= (_radius * 0.8) && distance <= _radius) {

    _color.a = _color.a <= 5 ? 5 : _color.a - 3;
    _color.g = _color.g <= 50 ? 50 : _color.g - 15;
    _color.b = _color.b <= 50 ? 50 : _color.b - 15;

  } else if (distance > _radius) {
    init();
    distance = 0;
  }
}

/*
 * Set the text and update the textbox size.
 */
void Target::setText(std::string txt, TTF_Font *font, int plus_x, int plus_y) {

  _font = font;
  _txt = txt;

  _plus_x = plus_x;
  _plus_y = plus_y == plus_x == 0 ? 1 : 0;

  TTF_SizeText(_font, char_ptr(), &_w, &_h);
  init();
}

/*
 * Reset fields (keep the current text)
 */
void Target::init() {
  _color = {255, 255, 255, 1};
  _position.x = _center.x - _w / 2;
  _position.y = _center.y - _h / 2;
}

// --
const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

point Target::position() const { return _position; };
int Target::h() const { return _h; }
int Target::w() const { return _w; }
