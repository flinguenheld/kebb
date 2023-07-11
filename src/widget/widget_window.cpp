#include "widget_window.h"

WidgetWindow::WidgetWindow(std::shared_ptr<WindowName> next_window, std::shared_ptr<Renderer> renderer)
    : _next_window(next_window), _renderer(renderer) {}
