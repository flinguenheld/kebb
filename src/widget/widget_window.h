#ifndef WIDGET_WINDOW_H
#define WIDGET_WINDOW_H

#include "renderer.h"
#include "widget/widget_base.h"
#include <memory>

enum class WindowName {
  W_None,
  W_Reception,
  W_Game,
  W_Pause,
  W_Option,
  W_Quit,
};

class WidgetWindow {
public:
  WidgetWindow(std::shared_ptr<WindowName> next_window);
  virtual ~WidgetWindow(){};

  virtual void control_left(){};
  virtual void control_right(){};
  virtual void control_up(){};
  virtual void control_down(){};

  virtual void control_enter(){};
  virtual void control_escape(){};

  virtual void control_others(uint16_t keycode){};

  virtual void controller(){};
  virtual void render(std::shared_ptr<Renderer> renderer){};

protected:
  boxsize _screen_size;
  uint16_t _scale_factor;

  std::shared_ptr<WindowName> _next_window;
};

#endif // !WIDGET_WINDOW_H
