#ifndef WINDOW_OPTION_H
#define WINDOW_OPTION_H

#include "option/option_file.h"
#include "utils.h"
#include "widget/button/widget_boolean.h"
#include "widget/button/widget_list.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_menu.h"
#include "widget/widget_window.h"
#include <algorithm>
#include <chrono>
#include <thread>
#include <vector>

class WindowOption : public WidgetWindowSelection {
public:
  WindowOption(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
               std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options);
  virtual ~WindowOption() override;

  virtual void control_escape() override;
  virtual void control_enter() override;
  virtual void control_left() override;
  virtual void control_right() override;

  virtual void render() override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_message;
  std::unique_ptr<WidgetMenu> _widget_menu;
  std::shared_ptr<OptionFile> _options;

  // Help message
  void display_message(std::string &&message);
  void check_new_resolution();
  void check_french_extra();
  bool _message_displayed;

  const kebb::boxsize _screen_size;
};
#endif // !WINDOW_OPTION_H
