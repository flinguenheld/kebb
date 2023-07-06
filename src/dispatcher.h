#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <algorithm>
#include <iostream>
#include <mutex>
#include <random>
#include <string>
#include <vector>

/*
 * Dispatcher class: its role is to distribute random chars and angles to threads in a
 * safe way.
 * Once a thread takes a char/angle, they are erase from lists.
 * This thread has to get it back with relase methods.
 */
class Dispatcher {
public:
  Dispatcher();

  int get_angle();
  void release_angle(int angle);

  char get_char();
  void release_char(char c);

private:
  std::vector<int> _angles;

  const std::string _letters;
  const std::string _capitals;
  const std::string _symbols;
  const std::string _numbers;
  std::string _char_list;

  std::mutex _mutex;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
  std::uniform_int_distribution<int> _random_angle;
};

#endif // DISPATCHER_H
