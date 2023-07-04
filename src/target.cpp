#include "target.h"

Target::Target(int x_area, int y_area, int radius_area)
    : _txt(), _font(nullptr), _center_area(x_area, y_area), _position(x_area, y_area),
      _radius_area(radius_area), _move_x(1), _move_y(1) {}

/*
 * Move the target and adapt fields according to the distance to the center
 */
void Target::update() {

  // move values are set in the setText method
  _position.x += _move_x;
  _position.y += _move_y;

  // Distance from the text center
  int distance = _center_area.distance(point{_position.x + _w / 2, _position.y + _h / 2});

  // Fade & colour --
  if (distance <= _radius_area * 0.2) {
    _color.a = _color.a > 200 ? 200 : _color.a + 5;

  } else if (distance >= (_radius_area * 0.8) && distance <= _radius_area) {

    _color.a = _color.a <= 5 ? 5 : _color.a - 3;
    _color.g = _color.g <= 50 ? 50 : _color.g - 15;
    _color.b = _color.b <= 50 ? 50 : _color.b - 15;

  } else if (distance > _radius_area) {
    init();
    distance = 0;
  }
}

/*
 * Set the text and update the textbox size.
 */
void Target::setText(std::string txt, TTF_Font *font, int angle) {

  // TODO: Validate the precision, see with the screen size and the scale !
  float angle_rad = angle * 3.14 / 180; // Hight precision is useless

  // Floats are impossible, so keep 2 numbers and use a scale (see renderer)
  _move_x = std::cos(angle_rad) * 10;
  _move_y = std::sin(angle_rad) * 10;

  std::cout << "_move x: " << _move_x << std::endl;

  _font = font;
  _txt = txt;

  TTF_SizeText(_font, char_ptr(), &_w, &_h);
  init();
}

/*
 * Reset fields (keep the current text)
 */
void Target::init() {
  _color = {255, 255, 255, 1};
  _position.x = _center_area.x - _w / 2;
  _position.y = _center_area.y - _h / 2;
}

// --
const char *Target::char_ptr() const { return _txt.c_str(); }
SDL_Color Target::color() const { return _color; }

point Target::position() const { return _position; };
int Target::h() const { return _h; }
int Target::w() const { return _w; }
