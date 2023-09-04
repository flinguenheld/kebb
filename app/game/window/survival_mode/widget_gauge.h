#ifndef WIDGET_GAUGE_H
#define WIDGET_GAUGE_H

#include "renderer.h"
#include "widget_textbox.h"
#include <algorithm>

/*
 * Render on the bottom right, a number with two char and a gauge.
 * This gauge is a triangle which increases according to the value given in the set_percentage() method.
 * The text allows to display the current level.
 */
class WidgetGauge {
public:
  WidgetGauge(widget::boxsize screen_size, std::shared_ptr<Renderer> renderer);

  void render() const;

  void set_percentage(uint16_t val);
  void set_level(uint16_t val);
  uint16_t get_level() const;

private:
  std::unique_ptr<WidgetTextBox> _widget_level;
  std::shared_ptr<Renderer> _renderer;

  std::vector<SDL_Vertex> _triangle;

  SDL_Color _gauge_color;
  const uint8_t _gauge_alpha;

  widget::boxsize _char_size;
  widget::point _pt_insertion; // Top left
  float _padding_y_txt;      // Used to reduce the gauge height
  float _x_hundred;          // x value for 100%
};

#endif // !WIDGET_GAUGE_H
