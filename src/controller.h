#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "target.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

class Controller {
public:
  Controller(std::shared_ptr<Score> score);
  void HandleInput(bool &running, std::vector<Target> &targets) const;

private:
  void check_targets(std::vector<Target> &targets, uint16_t k) const;

  uint16_t convert_us(SDL_Event &e) const;
  std::shared_ptr<Score> _score;
};

#endif
