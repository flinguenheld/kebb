#ifndef WINDOW_WELCOME_SURVIVAL_H
#define WINDOW_WELCOME_SURVIVAL_H

#include "button/widget_boolean.h"
#include "button/widget_list.h"
#include "button/widget_selection.h"
#include "file_option.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"
#include <cmath>
#include <thread>

class WindowWelcomeSurvival : public WidgetWindowSelection {
public:
  WindowWelcomeSurvival(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                        std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options);
  virtual ~WindowWelcomeSurvival() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  std::unique_ptr<WidgetTextBox> _textbox_title;
  std::unique_ptr<WidgetTextBox> _textbox_explanation_l1;
  std::unique_ptr<WidgetTextBox> _textbox_explanation_l2;

  std::unique_ptr<WidgetBottomMenu> _widget_menu;
  std::shared_ptr<OptionFile> _options;

  uint16_t max_fail(const std::string &difficulty);
  uint16_t max_miss(const std::string &difficulty);
  uint16_t next_level(const std::string &difficulty);
};
#endif // !WINDOW_WELCOME_SURVIVAL_H
