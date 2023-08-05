#ifndef WINDOW_WELCOME_H
#define WINDOW_WELCOME_H

#include "file/option_file.h"
#include "renderer.h"
#include "utils.h"
#include "welcome/widget_logo.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_textbox.h"
#include "widget/window/widget_bottom_menu.h"
#include "widget/window/widget_window.h"
#include <iterator>
#include <memory>
#include <thread>

class WindowWelcome : public WidgetWindowSelection {
public:
  WindowWelcome(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options);
  virtual ~WindowWelcome() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void render() const override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetBottomMenu> _widget_menu;
  std::shared_ptr<WidgetLogo> _widget_logo;

  std::thread _thread;

  std::shared_ptr<OptionFile> _options;
};

#endif // !WINDOW_WELCOME_H
