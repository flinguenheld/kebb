#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_ttf.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>

struct point {
  int x;
  int y;

  float distance(const point &pt) { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

class Target {

public:
  Target(int w_screen, int h_screen);
  void update();

  void setText(std::string txt, TTF_Font *font);

  const char *char_ptr() const;
  SDL_Color color() const;

  point top_left_position() const;

  int h() const;
  int w() const;

private:
  void init();

  TTF_Font *_font;
  std::string _txt;
  SDL_Color _color;

  const int _w_area, _h_aera;
  point _center_area;
  point _center_txt;
  point _top_left_position; // Current position
  int _h, _w;               // Textbox size
};

#endif // !TARGET_H
