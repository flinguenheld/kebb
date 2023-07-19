#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "SDL_stdinc.h"
#include "game/target.h"
#include "widget/widget_window.h"
#include <iostream>
#include <memory>
#include <vector>

class Controller {
public:
  Controller();
  void handle_input(bool &running, std::shared_ptr<WidgetWindow> window);

private:
  uint16_t convert_us(SDL_Event &e);

  const uint16_t _mask_mod; // Remove the first sixth bits (NUM/CAP/GUI) of mods

  bool _circumflex;
  bool _grave;
  bool _diaeresis;
};

#endif
