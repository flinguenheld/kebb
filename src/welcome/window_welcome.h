#ifndef WINDOW_WELCOME_H
#define WINDOW_WELCOME_H

#include "utils.h"
#include "widget/widget_menu.h"
#include "widget/widget_textbox.h"
#include "widget/widget_window.h"
#include <memory>

class WindowWelcome : public WidgetWindow {
public:
  WindowWelcome(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                std::shared_ptr<Renderer> renderer);
  virtual ~WindowWelcome();

  virtual void control_escape();
  virtual void control_enter();

  virtual void render();

private:
  std::unique_ptr<WidgetMenu> _widget_menu;
};

#endif // !WINDOW_WELCOME_H
