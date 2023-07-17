#include "target.h"
#include "widget/widget_base.h"
#include <cstdint>

// clang-format off
Target::Target(point center_area, uint16_t radius_area, boxsize char_size, uint16_t waiting_time,
    std::shared_ptr<Dispatcher> dispatcher, std::shared_ptr<Score> score) :

  WidgetTextBox(center_area, char_size),
      _active(true), _ok(false),
      _center_area(center_area),  _radius_area(radius_area),
      _waiting_time(waiting_time),
      _dispatcher(dispatcher), _score(score),
      _move_x(1), _move_y(1),
      _keycode(0), _angle(-1)
// clang-format on
{}

bool Target::check_keycode(uint16_t k) {

  if (_keycode == k) { // FIX: Need mutex ??
    _ok = true;
    return true;
  }
  return false;
}

void Target::stop() { _active = false; }

/*
 * Method for threads
 */
void Target::update() {

  init();
  uint16_t distance = 0;
  bool set_green = false;

  while (_active) {

    if (_ok) {
      if (_color_text.r != (50) || _color_text.g != (255) || _color_text.b != (50)) {
        _color_text = {50, 255, 50, 255}; // Set opaque green
        _score->up_sucess();
      }

      _color_text.a = _color_text.a <= 5 ? 5 : _color_text.a - 3; // Then fade away 🎵

      if (_color_text.a <= 5) {
        _dispatcher->release_angle(_angle);
        _dispatcher->release_keycode(_keycode);

        _ok = false;
        distance = 0;
        init();
      }
    } else {
      _position.x += _move_x; // Move values are set in the init method
      _position.y += _move_y;

      // Distance to the text center
      distance = _center_area.distance(point{static_cast<uint16_t>(_position.x + _size.w / 2),
                                             static_cast<uint16_t>(_position.y + _size.h / 2)});

      if (distance <= _radius_area * 0.2) {
        _color_text.a = _color_text.a > 200 ? 200 : _color_text.a + 5;

      } else if (distance >= (_radius_area * 0.8) && distance <= _radius_area) {
        _color_text.a = _color_text.a <= 5 ? 5 : _color_text.a - 3;
        _color_text.g = _color_text.g <= 50 ? 50 : _color_text.g - 15;
        _color_text.b = _color_text.b <= 50 ? 50 : _color_text.b - 15;

      } else if (distance > _radius_area) {
        _dispatcher->release_angle(_angle);
        _dispatcher->release_keycode(_keycode);

        _score->up_miss();
        init();
        distance = 0;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(_waiting_time));
  }
}

/*
 * Init the target, set the default position, ask information to the dispatcher
 * and calculate the new move increments.
 */
void Target::init() {

  _color_text = {255, 255, 255, 1};
  _position.x = _center_area.x - _size.w / 2;
  _position.y = _center_area.y - _size.h / 2;

  _angle = _dispatcher->get_angle();
  _keycode = _dispatcher->get_keycode();
  _text = keycode_to_string(_keycode);

  const float angle_rad = _angle * 3.14 / 180; // High precision is useless

  // Floats are impossible, so keep 2 numbers and use a scale (see renderer)
  _move_x = std::cos(angle_rad) * 10;
  _move_y = std::sin(angle_rad) * 10;
}
