#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL_events.h"
#include "snake.h"
#include "target.h"
#include <vector>

class Controller {
public:
  void HandleInput(bool &running, Snake &snake, std::vector<Target> &targets) const;

private:
  void check_targets(std::vector<Target> &targets, char c) const;
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;

  char convert_us(SDL_Event &e) const;
  char convert_fr(SDL_Event &e) const;
};

#endif
