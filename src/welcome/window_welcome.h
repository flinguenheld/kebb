#ifndef WINDOW_WELCOME_H
#define WINDOW_WELCOME_H

#include "renderer.h"
#include "utils.h"
#include "welcome/widget_logo.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_menu.h"
#include "widget/widget_textbox.h"
#include "widget/widget_window.h"
#include <iterator>
#include <memory>
#include <thread>

class WindowWelcome : public WidgetWindowSelection {
public:
  WindowWelcome(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                std::shared_ptr<Renderer> renderer);
  virtual ~WindowWelcome() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void render() override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetMenu> _widget_menu;
  std::shared_ptr<WidgetLogo> _widget_logo;

  std::thread _thread;
};

#endif // !WINDOW_WELCOME_H
