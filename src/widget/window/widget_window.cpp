#include "widget_window.h"

WidgetWindow::WidgetWindow(std::shared_ptr<uint8_t> next_window_id, std::shared_ptr<Renderer> renderer)
    : _next_window_id(next_window_id), _renderer(renderer) {}

// ----------------------------------------------------------------------------------------------------
// WIDGET WINDOW SELECTION ----------------------------------------------------------------------------
WidgetWindowSelection::WidgetWindowSelection(std::shared_ptr<uint8_t> next_window_id,
                                             std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window_id, renderer) {}

WidgetWindowSelection::~WidgetWindowSelection() {}

// -------------------------------------------------------------
// CONTROLS ----------------------------------------------------
void WidgetWindowSelection::control_up() {

  if (!_widget_select_fields.empty()) {
    std::vector<std::unique_ptr<WidgetSelection>>::iterator it = _widget_select_fields.begin();

    while (true) {
      if ((*it)->is_selected()) {
        (*it)->set_selected(false);

        if (it == _widget_select_fields.begin())
          it = _widget_select_fields.end() - 1;
        else
          --it;

        (*it)->set_selected(true);
        return;
      }
      ++it;
    }
  }
};
void WidgetWindowSelection::control_down() {

  if (!_widget_select_fields.empty()) {
    std::vector<std::unique_ptr<WidgetSelection>>::iterator it = _widget_select_fields.begin();

    while (true) {
      if ((*it)->is_selected()) {
        (*it)->set_selected(false);
        ++it;

        if (it == _widget_select_fields.end())
          it = _widget_select_fields.begin();

        (*it)->set_selected(true);
        return;
      }
      ++it;
    }
  }
}

void WidgetWindowSelection::control_left() {

  for (auto &w : _widget_select_fields) {
    if (w->is_selected()) {
      w->action_left();
      return;
    }
  }
}
void WidgetWindowSelection::control_right() {

  for (auto &w : _widget_select_fields) {
    if (w->is_selected()) {
      w->action_right();
      return;
    }
  }
}
