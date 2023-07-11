#include "widget_score.h"
#include "utils.h"
#include <cstdint>
#include <iostream>

WidgetScore::WidgetScore(WidgetScoreType type, boxsize screen_size, std::shared_ptr<Score> score,
                         std::shared_ptr<Renderer> renderer)
    : _score(score), _renderer(renderer) {

  // Geometry
  boxsize char_size = _renderer->char_size_score();
  boxsize line_size;
  point pt;

  // ------------------------------------------------------------------------
  // Success / Fail / Miss --------------------------------------------------
  if (type == WidgetScoreType::FullScreen) {

    char_size.set_scale(2);
    line_size.w = char_size.w * 13; // 13 chars in total for all lines (see render())
    line_size.h = char_size.h;

    pt.x = screen_size.w / 2 - line_size.w / 2;
    pt.y = line_size.h * 4.5;

  } else {

    line_size.w = char_size.w * 13;
    line_size.h = char_size.h;

    pt.x = screen_size.w - line_size.w - char_size.h * 0.1;
    pt.y = char_size.h * 0.1;
  }

  _textbox_success = std::make_unique<WidgetTextBox>(pt, line_size);
  pt.y += char_size.h;
  _textbox_fail = std::make_unique<WidgetTextBox>(pt, line_size);
  pt.y += char_size.h;
  _textbox_miss = std::make_unique<WidgetTextBox>(pt, line_size);

  // ------------------------------------------------------------------------
  // Timer ------------------------------------------------------------------
  char_size = _renderer->char_size_score();

  if (type == WidgetScoreType::FullScreen) {

    char_size.set_scale(4);
    line_size.w = char_size.w * 5;
    line_size.h = char_size.h;

    pt.x = screen_size.w / 2 - line_size.w / 2;
    pt.y = char_size.h * 0.7;

  } else {

    // Timer bigger and on the left --
    char_size.set_scale(1.5);
    line_size.w = char_size.w * 5;
    line_size.h = char_size.h;

    pt.x = char_size.h * 1.5 * 0.2;
    pt.y = char_size.h * 1.5 * 0.2;
  }
  _textbox_time = std::make_unique<WidgetTextBox>(pt, line_size);

  // Colors : Catpuccin Latte
  _textbox_time->set_color_text({137, 180, 250, 200});    // Blue
  _textbox_success->set_color_text({137, 180, 250, 200}); // Blue
  _textbox_fail->set_color_text({137, 180, 250, 200});    // Blue
  _textbox_miss->set_color_text({137, 180, 250, 200});    // Blue
}

void WidgetScore::render(uint16_t time_seconds) {

  _textbox_success->set_text("Success " + int_to_string(_score->success(), 5));
  _textbox_fail->set_text("Fail " + int_to_string(_score->fail(), 8));
  _textbox_miss->set_text("Miss " + int_to_string(_score->miss(), 8));

  _textbox_time->set_text(int_to_string(time_seconds / 60, 2, '0') + ":" +
                          int_to_string(time_seconds % 60, 2, '0'));

  _textbox_time->render(_renderer->renderer(), _renderer->font_score());
  _textbox_success->render(_renderer->renderer(), _renderer->font_score());
  _textbox_fail->render(_renderer->renderer(), _renderer->font_score());
  _textbox_miss->render(_renderer->renderer(), _renderer->font_score());
}

std::string WidgetScore::int_to_string(uint16_t i, uint8_t text_length, char c) {
  std::string text = std::to_string(i);
  while (text.length() < text_length)
    text.insert(0, 1, c);

  return text;
}
