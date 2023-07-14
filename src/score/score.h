#ifndef SCORE_H
#define SCORE_H

#include "utils.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>

class Score {

public:
  Score();

  void up_sucess();
  void up_fail();
  void up_miss();

  uint16_t success() const;
  uint16_t fail() const;
  uint16_t miss() const;

  void start_timer();
  int seconds_spent();
  int seconds_until_stop() const;

private:
  uint16_t _sucess;
  uint16_t _fail;
  uint16_t _miss;

  std::mutex _mutex;
  std::chrono::time_point<std::chrono::steady_clock> _timer_start;
  std::chrono::time_point<std::chrono::steady_clock> _timer_last_check;
};

#endif // DEBUG