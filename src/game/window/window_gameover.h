#ifndef WINDOW_GAMEOVER_H
#define WINDOW_GAMEOVER_H

#include "file/option_file.h"
#include "file/record_file.h"
#include "renderer.h"
#include "score/score.h"
#include "score/widget_score.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include "widget/window/widget_bottom_menu.h"
#include "widget/window/widget_window.h"
#include <memory>

class WindowGameOver : public WidgetWindow {
public:
  WindowGameOver(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                 std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                 std::shared_ptr<RecordFile> records, std::shared_ptr<OptionFile> options);
  virtual ~WindowGameOver() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  std::shared_ptr<Score> _score;
  std::shared_ptr<RecordFile> _records;
  std::shared_ptr<OptionFile> _options;

  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_mod;
  std::unique_ptr<WidgetTextBox> _widget_time;
  std::unique_ptr<WidgetTextBox> _widget_success;
  std::unique_ptr<WidgetTextBox> _widget_fail;
  std::unique_ptr<WidgetTextBox> _widget_miss;
  // std::unique_ptr<WidgetScore> _widget_score;
  std::unique_ptr<WidgetBottomMenu> _widget_menu;
};

#endif // !WINDOW_GAMEOVER_H
