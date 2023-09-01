#ifndef WIDGET_BASE_H
#define WIDGET_BASE_H

#include "SDL.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "utils.h"
#include <iostream>
#include <math.h>
#include <vector>

class WidgetBase {
public:
  WidgetBase(widget::point position, widget::boxsize size);
  virtual ~WidgetBase();
  virtual void render(SDL_Renderer *renderer) const {}
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const {}

  widget::point position() const;
  widget::boxsize size() const;
  SDL_Color color() const;

  void set_x(uint16_t x);
  void set_y(uint16_t y);
  void set_w(uint16_t w);
  void set_h(uint16_t h);
  void set_size(const widget::boxsize &s);
  void set_color(const SDL_Color &c);
  void set_visible(bool v);

protected:
  widget::point _position;
  widget::boxsize _size;
  SDL_Color _color;
  bool _visible;
};

#endif // !WIDGET_BASE_H
