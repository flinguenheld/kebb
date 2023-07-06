#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "target.h"

class Controller {
public:
  void HandleInput(bool &running, Snake &snake) const;

private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;

  void check_targets(char c);

  // std::shared_ptr<std::vector<Target>> _targets;
};

#endif
