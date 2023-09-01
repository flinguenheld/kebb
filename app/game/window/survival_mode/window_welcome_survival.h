#ifndef WINDOW_WELCOME_SURVIVAL_H
#define WINDOW_WELCOME_SURVIVAL_H

#include "button/widget_boolean.h"
#include "button/widget_list.h"
#include "button/widget_selection.h"
#include "file_option.h"
#include "kebb.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"
#include <cmath>
#include <cstdint>
#include <thread>

class WindowWelcomeSurvival : public WidgetWindowSelection {
public:
  WindowWelcomeSurvival(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                        std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options);
  virtual ~WindowWelcomeSurvival() override;

  virtual void control_escape() override;
  virtual void control_enter() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_explanation_l1;
  std::unique_ptr<WidgetTextBox> _widget_explanation_l2;
  std::unique_ptr<WidgetTextBox> _widget_explanation_l3;

  std::unique_ptr<WidgetBottomMenu> _widget_menu;
  std::shared_ptr<OptionFile> _options;

  void difficulty(uint16_t difficulty);
  uint16_t _max_fail, _max_miss;
  uint16_t _cost_fail, _cost_miss;
  uint16_t _next_level;
};
#endif // !WINDOW_WELCOME_SURVIVAL_H
