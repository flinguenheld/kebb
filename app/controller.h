#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "file/layout_file.h"
#include "window/widget_window.h"

class Controller {
public:
  Controller(std::shared_ptr<LayoutFile> layouts);
  void handle_input(bool &running, std::shared_ptr<WidgetWindow> window);

  void set_language();

private:
  uint16_t _dead_key_activated; // Memorise the current dead key's value (see layout files)
  bool _dead_key_deactivation;

  std::shared_ptr<LayoutFile> _layouts;
};

#endif
