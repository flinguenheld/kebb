#ifndef SCORE_H
#define SCORE_H

#include "renderer.h"
#include "widget/widget_base.h"
#include "widget/widget_textbox.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>

class Score {

public:
  Score(uint16_t screen_width, std::shared_ptr<Renderer> renderer);

  void render();

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

  std::shared_ptr<Renderer> _renderer;

  std::mutex _mutex;
  std::chrono::time_point<std::chrono::steady_clock> _timer_start;

  std::string int_to_string(uint16_t i, uint8_t text_length, char c = ' ');
};

#endif // DEBUG
