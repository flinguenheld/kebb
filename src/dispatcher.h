#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <algorithm>
#include <iostream>
#include <mutex>
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
  void release_txt(std::string letter);

private:
  std::vector<int> _used_angles;
  std::vector<std::string> _used_texts;
  std::string _char_list;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_angle;
  std::uniform_int_distribution<int> _random_txt;
};

#endif // DISPATCHER_H
