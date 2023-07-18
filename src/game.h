#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_blendmode.h"
#include "SDL_timer.h"
#include "SDL_ttf.h"
#include "about/window_about.h"
#include "controller.h"
#include "game/dispatcher.h"
#include "game/target.h"
#include "game/window_game.h"
#include "option/option_file.h"
#include "option/window_option.h"
#include "pause/window_pause.h"
#include "renderer.h"
#include "score/score.h"
#include "welcome/window_welcome.h"
#include "widget/widget_base.h"
#include "widget/widget_window.h"
#include <memory>

class Game {
public:
  Game(kebb::boxsize screen_size, std::shared_ptr<Score> score, std::shared_ptr<Renderer> renderer,
       std::shared_ptr<OptionFile> options);

  void run(Controller &controller);

private:
  std::shared_ptr<WidgetWindow> _current_window; // Shared with the controller

  std::vector<Target> _targets;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<Score> _score;
  std::shared_ptr<Renderer> _renderer;
  std::shared_ptr<OptionFile> _options;

  const kebb::boxsize _screen_size;
};

#endif
