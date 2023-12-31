#ifndef WINDOW_GAME_H
#define WINDOW_GAME_H

#include "file_option.h"
#include "file_record.h"
#include "game/score.h"
#include "game/target.h"
#include "game/window/widget_score.h"
#include "kebb.h"
#include "window/widget_window.h"

/*
 * This class is a mother for window games, it regroups variables, manages controls and give a base for the
 * render method.
 */
class WindowGame : public WidgetWindow {

public:
  WindowGame(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
             std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records,
             std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts);
  virtual ~WindowGame() override;

  virtual void control_escape() override;
  virtual void control_others(const std::string &character) override;
  virtual void render() const override;

  void stop_game();

protected:
  std::vector<std::shared_ptr<Target>> _targets;
  std::vector<std::thread> _threads;
  std::shared_ptr<Dispatcher> _dispatcher;
  std::shared_ptr<OptionFile> _options;
  std::shared_ptr<RecordFile> _records;
  std::shared_ptr<LayoutFile> _layouts;

  std::shared_ptr<Score> _score;
  std::unique_ptr<WidgetScore> _widget_score;

  widget::point _target_center_aera;
  uint16_t _target_radius_aera;

  uint16_t _nb_max_target;

  kebb::GameStatus _game_status;
  virtual void save_record() const {};
};

#endif // !WINDOW_GAME_H
