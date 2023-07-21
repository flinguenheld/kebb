#ifndef WIDGET_MENU_H
#define WIDGET_MENU_H

#include "renderer.h"
#include "widget/widget_textbox.h"
#include <memory>

class WidgetMenu {
public:
  WidgetMenu(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer, std::string &&text);
  void render() const;

private:
  std::unique_ptr<WidgetTextBox> _widget_textbox;
  std::shared_ptr<Renderer> _renderer;
};

#endif // !WIDGET_MENU_H
