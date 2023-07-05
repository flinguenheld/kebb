#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "dispatcher.h"
#include <iostream>
#include <math.h>
#include <memory>
#include <string>

struct point {
  int x;
  int y;

  point(int x, int y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

class Target {

public:
  Target(int x_area, int y_area, int radius_area, std::shared_ptr<Dispatcher> dispatcher);

  void update();
  void stop();

  void setFont(TTF_Font *font);

  std::string current_text() const;
  const char *char_ptr() const;
  SDL_Color color() const;

  point position() const;
  int h() const;
  int w() const;

private:
  void init();
  bool _active;

  std::shared_ptr<Dispatcher> _dispatcher;
  int _angle;

  TTF_Font *_font;
  std::string _current_text;
  SDL_Color _color;

  const point _center_area;
  const int _radius_area;

  point _position; // Real position (top left)
  int _h, _w;      // Textbox size

  int _move_x, _move_y;
};

#endif // !TARGET_H
