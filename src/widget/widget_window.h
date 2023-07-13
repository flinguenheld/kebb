#ifndef WIDGET_WINDOW_H
#define WIDGET_WINDOW_H

#include "renderer.h"
#include "widget/widget_base.h"
#include "widget/widget_selection.h"
#include <memory>

/*
 * Base class to create window. It regroups general fields, controls (empty) and have a shared_ptr which is
 * used to navigate to an other window.
 * The window list is set in utils.h.
 */
class WidgetWindow {
public:
  WidgetWindow(std::shared_ptr<WindowName> next_window, std::shared_ptr<Renderer> renderer);
  virtual ~WidgetWindow(){};

  virtual void control_left(){};
  virtual void control_right(){};
  virtual void control_up(){};
  virtual void control_down(){};

  virtual void control_enter(){};
  virtual void control_escape(){};

  virtual void control_others(uint16_t keycode){};

  virtual void controller(){};
  virtual void render(){};

protected:
  std::shared_ptr<WindowName> _next_window;
  std::shared_ptr<Renderer> _renderer;
};

/*
 * Same as WidgetWindow with an empty vector of WidgetSelection which allows to automaticaly manage
 * the up and down keys to navigate in fields.
 * You have to create your fields in the _widget_select_fields vector.
 */
class WidgetWindowSelection : public WidgetWindow {

public:
  WidgetWindowSelection(std::shared_ptr<WindowName> next_window, std::shared_ptr<Renderer> renderer);
  virtual ~WidgetWindowSelection(){};

  virtual void control_up();
  virtual void control_down();

protected:
  std::vector<std::unique_ptr<WidgetSelection>> _widget_select_fields;
};

#endif // !WIDGET_WINDOW_H
