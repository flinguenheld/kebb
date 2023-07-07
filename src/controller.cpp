#include "controller.h"
#include "SDL.h"
#include "SDL_events.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"
#include "snake.h"
#include <iostream>
#include <vector>

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::check_targets(std::vector<Target> &targets, char c) const {
  // Loop in all targets, if ok, up the loop
  for (auto &target : targets) {

    if (target.check_input(c))
      return;
  }

  std::cout << "Perdu !!!!! " << c << std::endl;
  // If not, fail
}

char Controller::convert_us(SDL_Event &e) const {

  if (e.key.keysym.mod == 4097) {

    std::cout << "SHIFT" << std::endl;
    switch (e.key.keysym.sym) {

    case SDLK_SLASH:
      return '?';
    case SDLK_2:
      return '@';
    }
  }

  return 'a';
}

char Controller::convert_fr(SDL_Event &e) const {

  if (e.key.keysym.mod == 4097) {

    // std::cout << "SHIFT" << std::endl;
    switch (e.key.keysym.sym) {

    case SDLK_SLASH:
      return '?';
    case SDLK_2:
      return '@';
    }
  } else {

    switch (e.key.keysym.sym) {

    case SDLK_1:
      return '&';
    case SDLK_3:
      return '"';
    }
  }

  return 'a';
}

void Controller::HandleInput(bool &running, Snake &snake, std::vector<Target> &targets) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {

      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
        break;

        // case SDLK_a:
        //   check_targets(targets, 'a');
        //   break;

      default:

        // check_targets(targets, convert_us(e));
        check_targets(targets, convert_fr(e));
      }
    }
  }
}
