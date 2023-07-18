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
  WidgetBase(kebb::point position, kebb::boxsize size);
  virtual ~WidgetBase();
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const {}
  virtual void render(SDL_Renderer *renderer) const {}

  kebb::point position() const;
  kebb::boxsize size() const;
  SDL_Color color() const;

  void set_x(uint16_t x);
  void set_y(uint16_t y);
  void set_w(uint16_t w);
  void set_h(uint16_t h);
  void set_size(const kebb::boxsize &s);
  void set_color(const SDL_Color &c);

protected:
  kebb::point _position;
  kebb::boxsize _size;
  SDL_Color _color;
};

#endif // !WIDGET_BASE_H
