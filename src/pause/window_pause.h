#ifndef WINDOW_PAUSE_H
#define WINDOW_PAUSE_H

#include "option/option_file.h"
#include "renderer.h"
#include "score/score.h"
#include "score/widget_score.h"
#include "widget/widget_base.h"
#include "widget/widget_menu.h"
#include "widget/widget_window.h"
#include <memory>

class WindowPause : public WidgetWindow {
public:
  WindowPause(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
              std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
              std::shared_ptr<OptionFile> options);
  virtual ~WindowPause() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  std::shared_ptr<Score> _score;
  std::unique_ptr<WidgetScore> _widget_score;
  std::unique_ptr<WidgetMenu> _widget_menu;
  std::shared_ptr<OptionFile> _options;
};

#endif // !WINDOW_PAUSE_H
