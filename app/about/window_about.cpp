#include "window_about.h"

WindowAbout::WindowAbout(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                         std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(4);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "About",
                                                  kebb::color(kebb::ColorName::C_Peach));
  pt.y += char_size.h * 1.2;

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.8);
  _widget_version = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Kebb 1.2.0",
                                                    kebb::color(kebb::ColorName::C_Yellow));
  pt.y += char_size.h * 1.1;
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.5);
  _widget_date = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "2023-08-29",
                                                 kebb::color(kebb::ColorName::C_Yellow));
  pt.y += char_size.h * 2.5;
  char_size = _renderer->font_char_size(FontName::F_Menu);
  _widget_github = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center,
                                                   "https://github.com/flinguenheld/kebb",
                                                   kebb::color(kebb::ColorName::C_Teal));
  pt.y += char_size.h * 1.4;
  _widget_email = std::make_unique<WidgetTextBox>(
      pt, char_size, TextBoxAlign::TB_Center, "florent@linguenheld.fr", kebb::color(kebb::ColorName::C_Teal));
}

WindowAbout::~WindowAbout() {}

void WindowAbout::render() const {

  _renderer->clear_screen();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_version->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_date->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_github->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_email->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowAbout::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
