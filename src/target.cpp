#include "target.h"

Target::Target(const std::string &txt) : _txt(txt) {}

void Target::update() {
  _x++;
  _y++;
}

std::string Target::txt() const { return _txt; }

int Target::x() const { return _x; }
int Target::y() const { return _y; }

int Target::h() const { return _h; }
int Target::w() const { return _w; }
