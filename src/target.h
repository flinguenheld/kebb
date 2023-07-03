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
  float distance(const point &pt) { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

class Target {

public:
  Target(int x, int y, int radius);
  void update();

  void setText(std::string txt, TTF_Font *font);

  const char *char_ptr() const;
  SDL_Color color() const;

  point position() const;
  int h() const;
  int w() const;

private:
  void init();

  TTF_Font *_font;
  std::string _txt;
  SDL_Color _color;

  point _center;
  int _radius;
  point _center_txt;
  point _position; // Top left position
  int _h, _w;      // Textbox size
};

#endif // !TARGET_H
