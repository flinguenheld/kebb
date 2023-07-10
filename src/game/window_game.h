#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "score.h"
#include "target.h"
#include "widget/widget_base.h"
#include "widget/widget_window.h"
#include <cstdint>
#include <memory>

class WindowGame : public WidgetWindow {

public:
  WindowGame(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<Score> score);

  virtual void controller();
  virtual void render(SDL_Renderer *_renderer, TTF_Font *font_target, TTF_Font *font_score);

  void start_threads();
  void stop_threads();

private:
  std::vector<Target> _targets;
  std::vector<std::thread> _threads;
  std::shared_ptr<Score> _score;
  std::shared_ptr<Dispatcher> _dispatcher;

  // TODO: rename them
  const point target_center_aera;
  const uint16_t target_radius_aera;
  const uint16_t target_font_size;
  const boxsize target_char_size;
};

#endif // !WINDOW_GAME_H
