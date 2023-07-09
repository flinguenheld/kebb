#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_timer.h"
#include "controller.h"
#include "dispatcher.h"
#include "renderer.h"
#include "score.h"
#include "target.h"
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
  Game(point target_center_aera, uint16_t target_radius_aera, boxsize target_char_size,
       std::shared_ptr<Score> score);
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);

private:
  std::vector<Target> _targets;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;
};

#endif
