#include "widget_score.h"
#include "widget_textbox.h"

WidgetScore::WidgetScore(kebb::boxsize screen_size, std::shared_ptr<Score> score,
                         std::shared_ptr<Renderer> renderer)
    : _score(score), _renderer(renderer) {

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Game);
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Success / Fail / Miss --------------------------------------------------
  pt.x = screen_size.w - char_size.w * 13 - char_size.h * 0.1; // 13 characters per line (arbitrarily)
  pt.y = char_size.h * 0.1;

  _textbox_success = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _textbox_success->set_color_text(kebb::color(kebb::ColorName::C_Blue));
  pt.y += char_size.h;
  _textbox_fail = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _textbox_fail->set_color_text(kebb::color(kebb::ColorName::C_Blue));
  pt.y += char_size.h;
  _textbox_miss = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _textbox_miss->set_color_text(kebb::color(kebb::ColorName::C_Blue));

  // ------------------------------------------------------------------------
  // Timer ------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Game).scale(1.7);

  pt.x = char_size.h * 1.5 * 0.2;
  pt.y = char_size.h * 1.5 * 0.2;

  _textbox_time = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Left);
  _textbox_time->set_color_text(kebb::color(kebb::ColorName::C_Peach));
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WidgetScore::logic(uint16_t time_seconds) {

  // 13 chars per line (arbitrarily)
  _textbox_success->move_text("Success " + kebb::adapt_string_length(std::to_string(_score->success()), 5));
  _textbox_fail->move_text("Fail " + kebb::adapt_string_length(std::to_string(_score->fail()), 8));
  _textbox_miss->move_text("Miss " + kebb::adapt_string_length(std::to_string(_score->miss()), 8));

  _textbox_time->move_text(kebb::adapt_string_length(std::to_string(time_seconds / 60), 2, '0') + ":" +
                           kebb::adapt_string_length(std::to_string(time_seconds % 60), 2, '0'));
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WidgetScore::render() const {

  _textbox_time->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _textbox_success->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _textbox_fail->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
  _textbox_miss->render(_renderer->renderer(), _renderer->font(FontName::F_Game));
}
