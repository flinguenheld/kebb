#ifndef WINDOW_ABOUT
#define WINDOW_ABOUT

#include "kebb.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"

class WindowAbout : public WidgetWindow {
public:
  WindowAbout(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
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
