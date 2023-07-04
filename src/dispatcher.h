#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <string>
#include <vector>

class Dispatcher {

public:
  Dispatcher();

  int get_angle();
  void release_angle(int angle);

  std::string get_txt();
  void release_txt();

private:
  std::vector<int> _used_angles;
  std::vector<std::string> _used_txt;
};

#endif // DISPATCHER_H
