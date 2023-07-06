#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include "dispatcher.h"
#include <chrono>
#include <iostream>
#include <math.h>
#include <memory>
#include <string>
#include <thread>

struct point {
  int x;
  int y;

  point(int x, int y) : x(x), y(y){};
  float distance(const point &pt) const { return sqrt(pow(x - pt.x, 2) + pow(y - pt.y, 2)); };
};

/*
 * Target is the logic part of a character.
 * The update method contains a while loop which is in charge of updating the object position. And thus the
 * color, the state ...
 * Once it's necessary, the init method is called. The latter will call the dispatcher to release the current
 * char/angle and ask for new ones.
 */
class Target {
public:
  Target(int x_area, int y_area, int radius_area, int font_size, std::shared_ptr<Dispatcher> dispatcher);

  void update();
  void stop();

  bool check_input(char c);

  std::string current_text() const;
  SDL_Color color() const;

  point position() const;
  int h() const;
  int w() const;

private:
  void init();
  bool _active;
  bool _ok;

  std::shared_ptr<Dispatcher> _dispatcher;

  char _char;
  int _angle;
  SDL_Color _color;

  const point _center_area;
  const int _radius_area;

  point _position;          // Real position (top left)
  int _target_h, _target_w; // Textbox size
  int _move_x, _move_y;     // Increments set according to the angle
};

#endif // !TARGET_H
