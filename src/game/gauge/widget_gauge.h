#ifndef WIDGET_GAUGE_H
#define WIDGET_GAUGE_H

#include "renderer.h"
#include "utils.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <memory>

class WidgetGauge {

public:
  WidgetGauge(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer);

  void render() const;

private:
  std::unique_ptr<WidgetTextBox> _textbox_level;
  std::shared_ptr<Renderer> _renderer;
};

#endif // !WIDGET_GAUGE_H

