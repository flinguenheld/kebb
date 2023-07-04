#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <math.h>
#include <string>

struct point {
  int x;
  int y;

  point(int x, int y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

class Target {

public:
  Target(int x_area, int y_area, int radius_area);
  void update();
  void stop();

  void setText(std::string txt, TTF_Font *font, int angle);

  const char *char_ptr() const;
  SDL_Color color() const;

  point position() const;
  int h() const;
  int w() const;

private:
  void init();
  bool _active;

  TTF_Font *_font;
  std::string _txt;
  SDL_Color _color;

  const point _center_area;
  const int _radius_area;

  point _position; // Real position (top left)
  int _h, _w;      // Textbox size

  int _move_x, _move_y;
};

#endif // !TARGET_H
