#include "widget_bottom_menu.h"

WidgetBottomMenu::WidgetBottomMenu(widget::boxsize screen_size, std::shared_ptr<Renderer> renderer,
                                   std::string &&text)
    : _renderer(renderer) {

  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt = {static_cast<uint16_t>(screen_size.w / 2),
                      static_cast<uint16_t>(screen_size.h - char_size.h * 0.8)};

  _widget_textbox = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, std::move(text),
                                                    widget::color(widget::ColorName::C_Overlay2));
}

void WidgetBottomMenu::render() const {
  _widget_textbox->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
}
