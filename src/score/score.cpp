#include "score.h"

Score::Score() : _sucess(0), _fail(0), _miss(0) {

  // TODO: Start the timer when the game is launch
  start_timer();
}

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

uint16_t Score::success() const { return _sucess; }
uint16_t Score::fail() const { return _fail; }
uint16_t Score::miss() const { return _miss; }
long Score::duration() const {
  return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock().now() - _timer_start)
      .count();
}
