#ifndef WIDGET_BASE_H
#define WIDGET_BASE_H

#include "SDL.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <cstdint>
#include <math.h>
#include <string>
#include <sys/types.h>
#include <vector>

struct point {
  uint16_t x;
  uint16_t y;

  point(uint16_t x, uint16_t y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

struct boxsize {
  uint16_t w;
  uint16_t h;
};

class WidgetBase {
public:
  WidgetBase(point position, boxsize size);
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const = 0;

  point position() const;
  boxsize size() const;
  SDL_Color color() const;

protected:
  point _position;
  boxsize _size;

  SDL_Color _color;
};

#endif // !WIDGET_BASE_H
