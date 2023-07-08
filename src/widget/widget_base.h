#ifndef WIDGET_BASE_H
#define WIDGET_BASE_H

#include "SDL.h"
#include <cstdint>
#include <math.h>
#include <string>
#include <sys/types.h>

struct point {
  uint16_t x;
  uint16_t y;

  point(uint16_t x, uint16_t y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

struct boxsize {
  uint16_t h;
  uint16_t w;
};

class WidgetBase {
public:
  WidgetBase(point position, boxsize size);
  SDL_Color color() const;

  point position() const;
  boxsize size() const;

private:
  point _position;
  boxsize _size;

  SDL_Color _color;
};

// class WidgetTextBoxBase : public WidgetBase {
//
// public:
//   WidgetTextBoxBase(point pos, boxsize size, uint16_t font_size);
//
// private:
//   SDL_Color _color_fg;
// };

#endif // WIDGET_BASE_H
