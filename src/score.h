#ifndef SCORE_H
#define SCORE_H

#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>

class Score {

public:
  Score(uint16_t screen_width, boxsize char_size);

  void render(SDL_Renderer *renderer, TTF_Font *font);

  void up_sucess();
  void up_fail();
  void up_miss();

  void start_timer();

private:
  std::unique_ptr<WidgetTextBox> _textbox_time;
  std::unique_ptr<WidgetTextBox> _textbox_success;
  std::unique_ptr<WidgetTextBox> _textbox_fail;
  std::unique_ptr<WidgetTextBox> _textbox_miss;

  uint16_t _sucess;
  uint16_t _fail;
  uint16_t _miss;

  std::mutex _mutex;
  std::chrono::time_point<std::chrono::steady_clock> _timer_start;

  std::string int_to_string(uint16_t i, uint8_t text_length, char c = ' ');
};

#endif // DEBUG
