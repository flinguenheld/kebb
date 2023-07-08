#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "dispatcher.h"
#include "keycodes.h"
#include "widget/widget_base.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <thread>

/*
 * Target is the logic part of a keycode (a character).
 * The update method contains a while loop which is in charge of updating the object position. And thus the
 * color, the state ...
 * Once it's necessary, the init method is called. The latter will call the dispatcher to release the current
 * keycode/angle and ask for new ones.
 */
class Target : public WidgetBase {
public:
  Target(uint16_t x_area, uint16_t y_area, uint16_t radius_area, uint16_t font_size,
         std::shared_ptr<Dispatcher> dispatcher);

  void update();
  void stop();

  bool check_keycode(uint16_t k);
  std::string current_text() const;

private:
  void init();
  bool _active;
  bool _ok;

  std::shared_ptr<Dispatcher> _dispatcher;

  uint16_t _keycode;
  uint16_t _angle;

  const point _center_area;
  const uint16_t _radius_area;

  uint16_t _move_x, _move_y; // Increments set according to the angle
};

#endif // !TARGET_H
