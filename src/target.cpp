#include "target.h"

Target::Target(int x_area, int y_area, int radius_area, int font_size, std::shared_ptr<Dispatcher> dispatcher)
    : _active(true), _current_text("Error"), _center_area(x_area, y_area), _position(x_area, y_area),
      _radius_area(radius_area), _move_x(1), _move_y(1), _dispatcher(dispatcher), _angle(-1),
      _target_h(font_size * 1.16), _target_w(font_size * 0.6), _test_chaaaaarr('L') {}

void Target::stop() { _active = false; }

/*
 * Move the target and adapt fields according to the distance to the center
 */
void Target::update() {

  init();

  while (_active) {

    // move values are set in the setText method
    _position.x += _move_x;
    _position.y += _move_y;

    // Distance from the text center
    int distance = _center_area.distance(point{_position.x + _target_w / 2, _position.y + _target_h / 2});

    // Fade & colour --
    if (distance <= _radius_area * 0.2) {
      _color.a = _color.a > 200 ? 200 : _color.a + 5;

    } else if (distance >= (_radius_area * 0.8) && distance <= _radius_area) {

      _color.a = _color.a <= 5 ? 5 : _color.a - 3;
      _color.g = _color.g <= 50 ? 50 : _color.g - 15;
      _color.b = _color.b <= 50 ? 50 : _color.b - 15;

    } else if (distance > _radius_area) {

      // _dispatcher->release_angle(_angle);
      // _dispatcher->release_txt(_current_text);

      init();
      distance = 0;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
  }
}

/*
 * Reset fields (keep the current text)
 */
void Target::init() {
  _color = {255, 255, 255, 1};
  _position.x = _center_area.x - _target_w / 2;
  _position.y = _center_area.y - _target_h / 2;

  _angle = _dispatcher->get_angle();
  // _angle = 50;

  float angle_rad = _angle * 3.14 / 180; // Hight precision is useless

  // TODO: Validate the precision, see with the screen size and the scale !
  // Floats are impossible, so keep 2 numbers and use a scale (see renderer)
  _move_x = std::cos(angle_rad) * 10;
  _move_y = std::sin(angle_rad) * 10;

  // --
  // _current_text = _dispatcher->get_txt();
  // _current_text = "B";
  _test_chaaaaarr = 'a';
  std::cout << "new letter: " << _current_text << std::endl;
}

// --
std::string Target::current_text() const {
  std::string t(1, _test_chaaaaarr);
  return t;
}
SDL_Color Target::color() const { return _color; }

point Target::position() const { return _position; };
int Target::h() const { return _target_h; }
int Target::w() const { return _target_w; }
