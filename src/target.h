#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "dispatcher.h"
#include "keycodes.h"
#include "score.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <iostream>
#include <string>
#include <thread>

/*
 * Target is the logic part of a keycode (a character).
 * The update method contains a while loop which is in charge of updating the object position. And thus the
 * color, the state ...
 * Once it's necessary, the init method is called. The latter will call the dispatcher to release the current
 * keycode/angle and ask for new ones.
 */
class Target : public WidgetTextBox {
public:
  Target(point center_area, uint16_t radius_area, boxsize char_size, std::shared_ptr<Dispatcher> dispatcher,
         std::shared_ptr<Score> score);

  void update();
  void stop();

  bool check_keycode(uint16_t k);

private:
  void init();
  bool _active;
  bool _ok;

  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;

  uint16_t _keycode;
  uint16_t _angle;

  const point _center_area;
  const uint16_t _radius_area;

  uint16_t _move_x, _move_y; // Increments set according to the angle
};

#endif // !TARGET_H
