#ifndef WIDGET_GAUGE_H
#define WIDGET_GAUGE_H

#include "renderer.h"
#include "utils.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <cstdint>
#include <memory>
#include <vector>

/*
 * Render on the bottom right, a number with two char and a gauge.
 * This gauge is a triangle which increases according to the value given in the set_percentage() method.
 * The text allows to display the current level.
 */
class WidgetGauge {
public:
  WidgetGauge(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer);

  void render() const;

  void set_percentage(uint16_t val);
  void set_text(std::string val);

private:
  std::unique_ptr<WidgetTextBox> _textbox_level;
  std::shared_ptr<Renderer> _renderer;

  std::vector<SDL_Vertex> _triangle;

  SDL_Color _color;
  const uint8_t _gauge_alpha;

  kebb::boxsize _char_size;
  kebb::point _pt_insertion; // Top left
  float _padding_y_txt;      // Used to reduce the gauge height
  float _x_hundred;          // x value for 100%
};

#endif // !WIDGET_GAUGE_H
