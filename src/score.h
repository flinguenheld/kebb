#ifndef SCORE_H
#define SCORE_H

#include "widget/widget_textbox.h"
#include <cstdint>
#include <memory>
#include <mutex>

class Score {

public:
  Score(point position, uint16_t font_size);

  void render(SDL_Renderer *renderer, TTF_Font *font);

  void up_sucess();
  void up_fail();
  void up_miss();

private:
  std::unique_ptr<WidgetTextBox> _textbox_time;
  std::unique_ptr<WidgetTextBox> _textbox_success;
  std::unique_ptr<WidgetTextBox> _textbox_fail;
  std::unique_ptr<WidgetTextBox> _textbox_miss;

  uint16_t _sucess;
  uint16_t _fail;
  uint16_t _miss;

  std::mutex _mutex;
};

#endif // DEBUG
