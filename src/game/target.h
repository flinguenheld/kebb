#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "dispatcher.h"
#include "game/score.h"
#include "utils.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <thread>

/*
 * Target is the logical part of a keycode (a character).
 * The update method contains a while loop which is in charge of updating the object position. And thus the
 * color, the state ...
 * Once it's necessary, the init method is called. The latter will call the dispatcher to release the current
 * keycode/angle and ask for a new one.
 */
class Target : public WidgetTextBox {
public:
  Target(kebb::point center_area, uint16_t radius_area, kebb::boxsize char_size, uint16_t speed,
         std::shared_ptr<Dispatcher> dispatcher, std::shared_ptr<Score> score,
         std::shared_ptr<LayoutFile> layouts);

  void update();
  void stop();

  void set_speed(uint16_t t); // Only updated by init()

  bool check_keycode(uint16_t k);

private:
  void init();
  bool _active;
  bool _ok;

  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;
  std::shared_ptr<LayoutFile> _layouts;

  uint16_t _keycode;
  uint16_t _angle;

  uint16_t _waiting_time;
  uint16_t _new_waiting_time;

  const kebb::point _center_area;
  const uint16_t _radius_area;

  uint16_t _move_x, _move_y; // Increments set according to the angle
  SDL_Color _green, _red, _white;
};

#endif // !TARGET_H
