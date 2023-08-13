#include "target.h"

// clang-format off
Target::Target(kebb::point center_area, uint16_t radius_area, kebb::boxsize char_size, uint16_t speed,
    std::shared_ptr<Dispatcher> dispatcher, std::shared_ptr<Score> score,std::shared_ptr<LayoutFile> layouts) :

  WidgetTextBox(center_area, char_size),
      _active(true), _ok(false),
      _center_area(center_area),
      _radius_area(radius_area),
      _waiting_time(10),
      _new_waiting_time(0),
      _dispatcher(dispatcher),
      _score(score),
      _layouts(layouts),
      _move_x(1), _move_y(1),
       _angle(-1)
// clang-format on
{
  set_speed(speed);

  _green = kebb::color(kebb::ColorName::C_Green);
  _red = kebb::color(kebb::ColorName::C_Red);
  _white = kebb::color(kebb::ColorName::C_Text);
}

bool Target::check_key(const std::string &c) {

  if (_text == c && !_ok) {
    _ok = true;
    return true;
  }
  return false;
}

// ----------------------------------------------------------------------------------------------------
// THREAD ---------------------------------------------------------------------------------------------
void Target::stop() { _active = false; }

void Target::update() {

  init();
  uint16_t distance = 0;
  bool set_green = false;

  while (_active) {

    if (_ok) {
      if (_color_text.r != (_green.r) || _color_text.g != (_green.g) || _color_text.b != (_green.b)) {
        _color_text = {_green.r, _green.g, _green.b, 255}; // Set opaque green
        _score->up_sucess();
      }

      _color_text.a = _color_text.a <= 5 ? 5 : _color_text.a - 3; // Then fade away 🎵

      if (_color_text.a <= 5) {
        _dispatcher->release_angle(_angle);
        _dispatcher->release_character(std::move(_text));

        _ok = false;
        distance = 0;
        init();
      }
    } else {
      _position.x += _move_x; // Move values are set in the init method
      _position.y += _move_y;

      // Distance to the text center
      distance = _center_area.distance(kebb::point{static_cast<uint16_t>(_position.x + _size.w / 2),
                                                   static_cast<uint16_t>(_position.y + _size.h / 2)});

      if (distance <= _radius_area * 0.2) {
        _color_text.a = _color_text.a > 200 ? 200 : _color_text.a + 5;

      } else if (distance >= (_radius_area * 0.8) && distance <= _radius_area) {
        _color_text.a = _color_text.a <= 5 ? 5 : _color_text.a - 3;
        _color_text.g = _color_text.g <= _red.g ? _red.g : _color_text.g - 15;
        _color_text.b = _color_text.b <= _red.b ? _red.b : _color_text.b - 15;

      } else if (distance > _radius_area) {
        _dispatcher->release_angle(_angle);
        _dispatcher->release_character(std::move(_text));

        _score->up_miss();
        init();
        distance = 0;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(_waiting_time));
  }
}

void set_waiting_time(uint16_t t) {}

/*
 * Init the target, set the default position, ask information to the dispatcher
 * and calculate the new move increments.
 */
void Target::init() {

  if (_new_waiting_time != 0) {
    _waiting_time = _new_waiting_time;
    _new_waiting_time = 0;
  }

  _color_text = {_white.r, _white.g, _white.b, 1};
  _position.x = _center_area.x - _size.w / 2;
  _position.y = _center_area.y - _size.h / 2;

  _angle = _dispatcher->get_angle();
  _dispatcher->get_character(_text);

  const float angle_rad = _angle * 3.14 / 180; // High precision is useless

  // Floats are impossible, so keep 2 numbers and use a scale (see renderer)
  _move_x = std::cos(angle_rad) * 10;
  _move_y = std::sin(angle_rad) * 10;
}

// ----------------------------------------------------------------------------------------------------
// TIME -----------------------------------------------------------------------------------------------
void Target::set_speed(uint16_t t) {

  switch (t) {
  case 1:
    _new_waiting_time = 38;
    break;
  case 2:
    _new_waiting_time = 34;
    break;
  case 3:
    _new_waiting_time = 30;
    break;
  case 4:
    _new_waiting_time = 28;
    break;
  case 5:
    _new_waiting_time = 26;
    break;
  case 6:
    _new_waiting_time = 24;
    break;
  case 7:
    _new_waiting_time = 22;
    break;
  case 8:
    _new_waiting_time = 20;
    break;
  case 9:
    _new_waiting_time = 18;
    break;
  case 10:
    _new_waiting_time = 16;
    break;
  case 11:
    _new_waiting_time = 14;
    break;
  case 12:
    _new_waiting_time = 12;
    break;
  case 13:
    _new_waiting_time = 10;
    break;
  case 14:
    _new_waiting_time = 8;
    break;
  case 15:
    _new_waiting_time = 6;
    break;
  case 16:
    _new_waiting_time = 5;
    break;
  case 17:
    _new_waiting_time = 4;
    break;
  case 18:
    _new_waiting_time = 3;
    break;
  case 19:
    _new_waiting_time = 2;
    break;
  default:
    _new_waiting_time = 1;
  }
}
