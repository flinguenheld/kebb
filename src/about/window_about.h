#ifndef WINDOW_ABOUT
#define WINDOW_ABOUT

#include "utils.h"
#include "widget/window/widget_bottom_menu.h"
#include "widget/window/widget_window.h"
#include <memory>

class WindowAbout : public WidgetWindow {
public:
  WindowAbout(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
              std::shared_ptr<Renderer> renderer);
  virtual ~WindowAbout() override;

  virtual void control_escape() override;
  virtual void render() const override;

private:
  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_version;
  std::unique_ptr<WidgetTextBox> _widget_date;
  std::unique_ptr<WidgetTextBox> _widget_github;
  std::unique_ptr<WidgetTextBox> _widget_email;

  std::unique_ptr<WidgetBottomMenu> _widget_menu;
};

#endif // !WINDOW_ABOUT
