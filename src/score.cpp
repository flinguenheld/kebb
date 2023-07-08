#include "score.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

Score::Score(point position, uint16_t font_size) : _sucess(0), _fail(0), _miss(0) {

  // Geometry

  auto a = std::make_shared<int>();

  boxsize bs = {1000, 500};
  _textbox_success = std::make_unique<WidgetTextBox>(position, bs);
  position.y += 500;
  _textbox_fail = std::make_unique<WidgetTextBox>(position, bs);
  position.y += 500;
  _textbox_miss = std::make_unique<WidgetTextBox>(position, bs);
}

void Score::render(SDL_Renderer *renderer, TTF_Font *font) {

  std::unique_lock<std::mutex> ul(_mutex);
  _textbox_success->set_text("Success: " + std::to_string(_sucess));
  _textbox_fail->set_text("Fail: " + std::to_string(_fail));
  _textbox_miss->set_text("Miss: " + std::to_string(_miss));
  ul.unlock();

  // _textbox_time->render(renderer, font);
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
