#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_timer.h"
#include "controller.h"
#include "game/dispatcher.h"
#include "game/target.h"
#include "game/window_game.h"
#include "renderer.h"
#include "score/score.h"
#include "welcome/window_welcome.h"
#include "widget/widget_base.h"
#include "widget/widget_window.h"
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
  Game(boxsize screen_size, std::shared_ptr<Score> score, std::shared_ptr<Renderer> renderer);
  ~Game();

  void Run(Controller const &controller, std::size_t target_frame_duration);

private:
  // TODO: Regroup with other windows

  WidgetWindow *_current_window;

  std::vector<Target> _targets;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;
  std::shared_ptr<Renderer> _renderer;

  const boxsize _screen_size;
};

#endif
