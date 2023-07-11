#ifndef WINDOW_PAUSE_H
#define WINDOW_PAUSE_H

#include "score/score.h"
#include "score/widget_score.h"
#include "widget/widget_base.h"
#include "widget/widget_window.h"

class WindowPause : public WidgetWindow {
public:
  WindowPause(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<WindowName> next_window,
              std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score);
  virtual ~WindowPause();

  virtual void control_escape();
  virtual void control_enter();

  virtual void control_up();
  virtual void control_down();
  virtual void render();

private:
  std::shared_ptr<Score> _score;
  std::unique_ptr<WidgetScore> _widget_score;
};

#endif // !WINDOW_PAUSE_H
