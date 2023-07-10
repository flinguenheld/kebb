#ifndef WIDGET_WINDOW_H
#define WIDGET_WINDOW_H

#include <cstdint>
#include <sys/types.h>
class WidgetWindow {
public:
  virtual void control_left(){};
  virtual void control_right(){};
  virtual void control_up(){};
  virtual void control_down(){};

  virtual void control_enter(){};
  virtual void control_escape(){};

  virtual void control_others(uint16_t keycode){};

  virtual void controller(){};
  virtual void render(){};

private:
};

#endif // !WIDGET_WINDOW_H
