#include "widget_bottom_menu.h"
#include "utils.h"
#include "widget_textbox.h"

WidgetBottomMenu::WidgetBottomMenu(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer,
                                   std::string &&text)
    : _renderer(renderer) {

  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::point pt = {static_cast<uint16_t>(screen_size.w / 2),
                    static_cast<uint16_t>(screen_size.h - char_size.h * 0.8)};

  _widget_textbox = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, std::move(text),
                                                    kebb::color(kebb::ColorName::C_Overlay2));
}

void WidgetBottomMenu::render() const {
  _widget_textbox->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
}
