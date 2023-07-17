#include "score.h"
#include <chrono>

Score::Score() : _sucess(0), _fail(0), _miss(0) {}

void Score::start_timer() { _timer_start = std::chrono::steady_clock().now(); }

void Score::up_sucess() {
  std::unique_lock<std::mutex> ul(_mutex);
  _sucess++;
}
void Score::up_fail() {
  std::unique_lock<std::mutex> ul(_mutex);
  _fail++;
}
void Score::up_miss() {
  std::unique_lock<std::mutex> ul(_mutex);
  _miss++;
}

void Score::reset() {
  _sucess = 0;
  _fail = 0;
  _miss = 0;
};

uint16_t Score::success() const { return _sucess; }
uint16_t Score::fail() const { return _fail; }
uint16_t Score::miss() const { return _miss; }
int Score::seconds_spent() {
  _timer_last_check = std::chrono::steady_clock().now();
  return std::chrono::duration_cast<std::chrono::seconds>(_timer_last_check - _timer_start).count();
}

int Score::seconds_until_stop() const {
  return std::chrono::duration_cast<std::chrono::seconds>(_timer_last_check - _timer_start).count();
}
