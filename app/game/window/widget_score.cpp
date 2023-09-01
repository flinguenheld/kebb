#include "widget_score.h"

WidgetScore::WidgetScore(widget::boxsize screen_size, std::shared_ptr<Score> score,
                         std::shared_ptr<Renderer> renderer)
    : _score(score), _renderer(renderer) {

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Game);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Success / Fail / Miss --------------------------------------------------
  pt.x = screen_size.w - char_size.w * 13 - char_size.h * 0.1; // 13 characters per line (arbitrarily)
  pt.y = char_size.h * 0.1;

  _widget_success = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _widget_success->set_color_text(widget::color(widget::ColorName::C_Blue));
  pt.y += char_size.h;
  _widget_fail = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _widget_fail->set_color_text(widget::color(widget::ColorName::C_Blue));
  pt.y += char_size.h;
  _widget_miss = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _widget_miss->set_color_text(widget::color(widget::ColorName::C_Blue));

  // ------------------------------------------------------------------------
  // Timer ------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Game).scale(1.7);

  pt.x = char_size.h * 1.5 * 0.2;
  pt.y = char_size.h * 1.5 * 0.2;

  _widget_time = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _widget_time->set_color_text(widget::color(widget::ColorName::C_Peach));
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WidgetScore::logic(uint16_t time_seconds) {

  // 13 chars per line (arbitrarily)
  _widget_success->move_text("Success " + widget::adapt_string_length(std::to_string(_score->success()), 5));
  _widget_fail->move_text("Fail " + widget::adapt_string_length(std::to_string(_score->fail()), 8));
  _widget_miss->move_text("Miss " + widget::adapt_string_length(std::to_string(_score->miss()), 8));

  _widget_time->move_text(widget::adapt_string_length(std::to_string(time_seconds / 60), 2, '0') + ":" +
                          widget::adapt_string_length(std::to_string(time_seconds % 60), 2, '0'));
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WidgetScore::render() const {

  _widget_time->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _widget_success->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _widget_fail->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _widget_miss->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
}
