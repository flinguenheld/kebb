#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "game/target.h"
#include "widget/widget_window.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class Controller {
public:
  void HandleInput(bool &running, WidgetWindow *window) const;

private:
  uint16_t convert_us(SDL_Event &e) const;
};

#endif
