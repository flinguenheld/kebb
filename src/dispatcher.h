#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

class Dispatcher {

  // FIX: Mutex !!!

public:
  Dispatcher();

  int get_angle();
  void release_angle(int angle);

  std::string get_txt();
  void release_txt();

private:
  std::vector<int> _used_angles;
  std::vector<std::string> _used_txt;
  std::vector<char> _chars;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_angle;
  std::uniform_int_distribution<int> _random_txt;
};

#endif // DISPATCHER_H
