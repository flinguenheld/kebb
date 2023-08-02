#include "widget_gauge.h"

WidgetGauge::WidgetGauge(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer)
    : _renderer(renderer) {

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::boxsize line_size;
  kebb::point pt;

  _textbox_level = std::make_unique<WidgetTextBox>(pt, line_size);

  _textbox_level->set_color_text(kebb::color(kebb::ColorName::C_Peach));
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WidgetGauge::render() const {
  _textbox_level->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
}
