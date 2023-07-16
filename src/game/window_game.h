#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "option/option_file.h"
#include "renderer.h"
#include "score/score.h"
#include "score/widget_score.h"
#include "target.h"
#include "widget/widget_base.h"
#include "widget/widget_window.h"
#include <cstdint>
#include <memory>
#include <sys/types.h>

class WindowGame : public WidgetWindow {

public:
  WindowGame(boxsize screen_size, std::shared_ptr<WindowName> next_window, std::shared_ptr<Renderer> renderer,
             std::shared_ptr<Score> score, std::shared_ptr<OptionFile> options);
  virtual ~WindowGame();

  virtual void control_escape();
  virtual void control_others(uint16_t keycode);
  virtual void render();

  void stop_threads();

private:
  std::vector<Target> _targets;
  std::vector<std::thread> _threads;
  std::shared_ptr<Dispatcher> _dispatcher;

  std::shared_ptr<Score> _score;
  std::unique_ptr<WidgetScore> _widget_score;

  // TODO: Usefull or not ?
  const point _target_center_aera;
  const uint16_t _target_radius_aera;

  uint16_t _countdown_value; // Seconds
};

#endif // !WINDOW_GAME_H
