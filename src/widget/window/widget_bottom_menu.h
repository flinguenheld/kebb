#ifndef WIDGET_BOTTOM_MENU_H
#define WIDGET_BOTTOM_MENU_H

#include "renderer.h"
#include "widget_textbox.h"
#include <memory>

/*
 * Display a textbox which allows you to indicate user actions.
 */
class WidgetBottomMenu {
public:
  WidgetBottomMenu(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer, std::string &&text);
  void render() const;

private:
  std::unique_ptr<WidgetTextBox> _widget_textbox;
  std::shared_ptr<Renderer> _renderer;
};

#endif // !WIDGET_BOTTOM_MENU_H
