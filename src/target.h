#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_ttf.h"
#include <algorithm>
#include <iostream>
#include <string>

class Target {

public:
  Target(int w_screen, int h_screen);
  void update();

  void setText(std::string txt, TTF_Font *font);

  const char *char_ptr() const;
  SDL_Color color() const;

  int x() const;
  int y() const;

  int h() const;
  int w() const;

private:
  void init();

  TTF_Font *_font;
  std::string _txt;
  SDL_Color _color;

  const int _w_screen, _h_screen;
  int _x, _y;
  int _h, _w;
};

#endif // !TARGET_H
