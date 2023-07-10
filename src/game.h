#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_timer.h"
#include "controller.h"
#include "game/dispatcher.h"
#include "game/target.h"
#include "game/window_game.h"
#include "renderer.h"
#include "score.h"
#include "widget/widget_base.h"
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

class Game {
public:
  Game(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<Score> score);
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

private:
  // TODO: Regroup with other windows
  WindowGame _w_game;

  std::vector<Target> _targets;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;
};

#endif
