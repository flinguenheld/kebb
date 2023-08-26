#ifndef WIDGET_SCORE_H
#define WIDGET_SCORE_H

#include "game/score.h"
#include "renderer.h"
#include "widget_textbox.h"

class WidgetScore {
public:
  WidgetScore(kebb::boxsize screen_size, std::shared_ptr<Score> score, std::shared_ptr<Renderer> renderer);

  void logic(uint16_t time_seconds);
  void render() const;

private:
  std::unique_ptr<WidgetTextBox> _textbox_time;
  std::unique_ptr<WidgetTextBox> _textbox_success;
  std::unique_ptr<WidgetTextBox> _textbox_fail;
  std::unique_ptr<WidgetTextBox> _textbox_miss;

  std::shared_ptr<Score> _score;
  std::shared_ptr<Renderer> _renderer;
};

#endif // !WIDGET_SCORE_H
