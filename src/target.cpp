#include "target.h"
#include "keycodes.h"
#include <cstdint>

// clang-format off
Target::Target(uint16_t x_area, uint16_t y_area, uint16_t radius_area, uint16_t font_size,
    std::shared_ptr<Dispatcher> dispatcher) :
      _active(true), _ok(false),
      _center_area(x_area, y_area), _position(x_area, y_area), _radius_area(radius_area),
      _target_h(font_size * 1.16), _target_w(font_size * 0.6),
      _dispatcher(dispatcher),
      _move_x(1), _move_y(1),
      _keycode(0), _angle(-1)
// clang-format on
{}

/*
 * Method for threads
 */
void Target::update() {

  init();
  uint16_t distance = 0;
  bool set_green = false;

  while (_active) {

    if (_ok) {
      if (!set_green) {
        _color = {50, 255, 50, 255};
        set_green = true;
      } else {
        _color.a = _color.a <= 5 ? 5 : _color.a - 3; // Fade away 🎵

        if (_color.a <= 5) {
          _dispatcher->release_angle(_angle);
          _dispatcher->release_keycode(_keycode);

          set_green = false;
          _ok = false;

          distance = 0;
          init();
        }
      }
    } else {
      _position.x += _move_x; // Move values are set in the init method
      _position.y += _move_y;

      // Distance to the text center
      distance = _center_area.distance(point{static_cast<uint16_t>(_position.x + _target_w / 2),
                                             static_cast<uint16_t>(_position.y + _target_h / 2)});

      if (distance <= _radius_area * 0.2) {
        _color.a = _color.a > 200 ? 200 : _color.a + 5;

      } else if (distance >= (_radius_area * 0.8) && distance <= _radius_area) {
        _color.a = _color.a <= 5 ? 5 : _color.a - 3;
        _color.g = _color.g <= 50 ? 50 : _color.g - 15;
        _color.b = _color.b <= 50 ? 50 : _color.b - 15;

      } else if (distance > _radius_area) {
        _dispatcher->release_angle(_angle);
        _dispatcher->release_keycode(_keycode);

        init();
        distance = 0;
        // TODO: Up score -1
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

/*
 * Stop the update while loop.
 */
void Target::stop() { _active = false; }

/*
 * Init the target, set the default position, ask information to the dispatcher
 * and calculate the new move increments.
 */
void Target::init() {
  _color = {255, 255, 255, 1};
  _position.x = _center_area.x - _target_w / 2;
  _position.y = _center_area.y - _target_h / 2;

  _keycode = _dispatcher->get_keycode();
  _angle = _dispatcher->get_angle();

  const float angle_rad = _angle * 3.14 / 180; // Hight precision is useless

  // Floats are impossible, so keep 2 numbers and use a scale (see renderer)
  _move_x = std::cos(angle_rad) * 10;
  _move_y = std::sin(angle_rad) * 10;
}

// FIX: Mutex ??
bool Target::check_keycode(uint16_t k) {
  if (_keycode == k) {
    _ok = true;
    return true;
  }
  return false;
}

std::string Target::current_text() const { return keycode_to_string(_keycode); }
SDL_Color Target::color() const { return _color; }
point Target::position() const { return _position; };
uint16_t Target::h() const { return _target_h; }
uint16_t Target::w() const { return _target_w; }
