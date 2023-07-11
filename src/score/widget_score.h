#ifndef WIDGET_SCORE_H
#define WIDGET_SCORE_H

#include "renderer.h"
#include "score.h"
#include "utils.h"
#include "widget/widget_textbox.h"
#include <memory>

enum class WidgetScoreType {
  FullScreen,
  Top,
};

class WidgetScore {
public:
  WidgetScore(WidgetScoreType type, boxsize screen_size, std::shared_ptr<Score> score,
              std::shared_ptr<Renderer> renderer);
  void render(uint16_t time_seconds);

private:
  std::unique_ptr<WidgetTextBox> _textbox_time;
  std::unique_ptr<WidgetTextBox> _textbox_success;
  std::unique_ptr<WidgetTextBox> _textbox_fail;
  std::unique_ptr<WidgetTextBox> _textbox_miss;

  std::shared_ptr<Score> _score;
  std::shared_ptr<Renderer> _renderer;

  std::string int_to_string(uint16_t i, uint8_t text_length, char c = ' ');
};

#endif // !WIDGET_SCORE_H
