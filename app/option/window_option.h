#ifndef WINDOW_OPTION_H
#define WINDOW_OPTION_H

#include "button/widget_boolean.h"
#include "button/widget_list.h"
#include "button/widget_selection.h"
#include "file_layout.h"
#include "file_option.h"
#include "kebb.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"
#include <thread>
#include <vector>

class WindowOption : public WidgetWindowSelection {
public:
  WindowOption(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
               std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options,
               std::shared_ptr<LayoutFile> layouts);
  virtual ~WindowOption() override;

  virtual void control_escape() override;
  virtual void control_enter() override;
  virtual void control_left() override;
  virtual void control_right() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_message;
  std::unique_ptr<WidgetBottomMenu> _widget_menu;

  std::shared_ptr<OptionFile> _options;
  std::shared_ptr<LayoutFile> _layouts;

  // Help message
  void check_new_resolution();
  void check_qwerty_extra();
  bool _message_displayed;

  const widget::boxsize _screen_size;
};
#endif // !WINDOW_OPTION_H
