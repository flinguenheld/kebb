#include "score.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

Score::Score(point position, uint16_t font_size) : _sucess(0), _fail(0), _miss(0) {

  // Geometry

  auto a = std::make_shared<int>();

  boxsize bs = {1000, 800};
  _textbox_time = std::make_unique<WidgetTextBox>(position, bs);
  position.y += 500;
  _textbox_success = std::make_unique<WidgetTextBox>(position, bs);
  position.y += 500;
  _textbox_fail = std::make_unique<WidgetTextBox>(position, bs);
  position.y += 500;
  _textbox_miss = std::make_unique<WidgetTextBox>(position, bs);

  _textbox_time->set_color_text({97, 132, 249, 250});
  _textbox_success->set_color_text({97, 132, 249, 250});
  _textbox_fail->set_color_text({97, 132, 249, 250});
  _textbox_miss->set_color_text({97, 132, 249, 250});

  // TODO: Start the timer when the game is launch
  start_timer();
}

void Score::start_timer() { _timer_start = std::chrono::steady_clock().now(); }

void Score::render(SDL_Renderer *renderer, TTF_Font *font) {

  std::unique_lock<std::mutex> ul(_mutex);
  _textbox_success->set_text("Success: " + std::to_string(_sucess));
  _textbox_fail->set_text("Fail: " + std::to_string(_fail));
  _textbox_miss->set_text("Miss: " + std::to_string(_miss));
  ul.unlock();

  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock().now() - _timer_start)
          .count();

  _textbox_time->set_text("Time: " + std::to_string(duration / 60) + ":" + std::to_string(duration % 60));

  _textbox_time->render(renderer, font);
  _textbox_success->render(renderer, font);
  _textbox_fail->render(renderer, font);
  _textbox_miss->render(renderer, font);
}

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
