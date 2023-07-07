#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "dispatcher.h"
#include "keycodes.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <thread>

struct point {
  uint16_t x;
  uint16_t y;

  point(uint16_t x, uint16_t y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

/*
 * Target is the logic part of a keycode (a character).
 * The update method contains a while loop which is in charge of updating the object position. And thus the
 * color, the state ...
 * Once it's necessary, the init method is called. The latter will call the dispatcher to release the current
 * keycode/angle and ask for new ones.
 */
class Target {
public:
  Target(uint16_t x_area, uint16_t y_area, uint16_t radius_area, uint16_t font_size,
         std::shared_ptr<Dispatcher> dispatcher);

  void update();
  void stop();

  bool check_keycode(uint16_t k);

  std::string current_text() const;
  SDL_Color color() const;

  point position() const;
  uint16_t h() const;
  uint16_t w() const;

private:
  void init();
  bool _active;
  bool _ok;

  std::shared_ptr<Dispatcher> _dispatcher;

  uint16_t _keycode;
  uint16_t _angle;
  SDL_Color _color;

  const point _center_area;
  const uint16_t _radius_area;

  point _position;               // Real position (top left)
  uint16_t _target_h, _target_w; // Textbox size
  uint16_t _move_x, _move_y;     // Increments set according to the angle
};

#endif // !TARGET_H
