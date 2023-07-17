#ifndef WIDGET_BASE_H
#define WIDGET_BASE_H

#include "SDL.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "utils.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

class WidgetBase {
public:
  WidgetBase(point position, boxsize size);
  virtual ~WidgetBase();
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const {}
  virtual void render(SDL_Renderer *renderer) const {}

  point position() const;
  boxsize size() const;
  SDL_Color color() const;

  void set_x(uint16_t x);
  void set_y(uint16_t y);
  void set_w(uint16_t w);
  void set_h(uint16_t h);
  void set_size(const boxsize &s);
  void set_color(const SDL_Color &c);

protected:
  point _position;
  boxsize _size;
  SDL_Color _color;
};

#endif // !WIDGET_BASE_H
