#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <mutex>
#include <random>
#include <string>
#include <vector>

class Dispatcher {

public:
  Dispatcher();

  int get_angle();
  void release_angle(int angle);

  char get_char();
  void release_char(char c);

private:
  std::vector<int> _angles;
  std::string _char_list;

  std::string _letters;
  std::string _capitals;
  std::string _symbols;
  std::string _numbers;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_angle;
};

#endif // DISPATCHER_H
