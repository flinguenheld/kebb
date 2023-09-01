#ifndef WINDOW_WELCOME_H
#define WINDOW_WELCOME_H

#include "button/widget_selection.h"
#include "file_option.h"
#include "kebb.h"
#include "welcome/widget_logo.h"
#include "widget_textbox.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"
#include <thread>

class WindowWelcome : public WidgetWindowSelection {
public:
  WindowWelcome(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
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
