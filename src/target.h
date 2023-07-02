#ifndef TARGET_H
#define TARGET_H

#include "SDL.h"
#include <string>

class Target {

public:
  Target(const std::string &txt);
  void update();

  std::string txt() const;

  int x() const;
  int y() const;

  int h() const;
  int w() const;

private:
  std::string _txt;

  int _x, _y;
  int _h, _w;
};

#endif // !TARGET_H
