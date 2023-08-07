#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include "SDL_render.h"
#include "SDL_ttf.h"
#include "file/option_file.h"
#include "file/record_file.h"
#include "game/target.h"
#include "renderer.h"
#include "score/score.h"
#include "score/widget_score.h"
#include "widget/widget_base.h"
#include "widget/window/widget_window.h"
#include <cstdint>
#include <memory>
#include <sys/types.h>

/*
 * This class is a mother for window games, it regroups variables, manages controls and give a base for the
 * render method.
 */
class WindowGame : public WidgetWindow {

public:
  WindowGame(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
             std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
             std::shared_ptr<RecordFile> records, std::shared_ptr<OptionFile> options);
  virtual ~WindowGame() override;

  virtual void control_escape() override;
  virtual void control_others(uint16_t keycode) override;
  virtual void render() const override;

  void stop_threads();

protected:
  std::vector<std::shared_ptr<Target>> _targets;
  std::vector<std::thread> _threads;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<OptionFile> _options;
  std::shared_ptr<RecordFile> _records;

  std::shared_ptr<Score> _score;
  std::unique_ptr<WidgetScore> _widget_score;

  kebb::point _target_center_aera;
  uint16_t _target_radius_aera;

  uint16_t _nb_max_target;

  kebb::GameStatus _game_status;
  virtual void save_record() const {};
};

#endif // !WINDOW_GAME_H
