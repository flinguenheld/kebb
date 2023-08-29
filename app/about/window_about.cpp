#include "window_about.h"

WindowAbout::WindowAbout(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                         std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::boxsize bs;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  // Catppuccin: Mocha
  char_size.set_scale(3);
  bs.w = char_size.w * 5;
  bs.h = char_size.h;

  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y = bs.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs);
  _widget_title->set_text("About");
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  char_size.set_scale(1.1);

  bs.w = char_size.w * 8;
  bs.h = char_size.h;
  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += bs.h * 1.4;
  _widget_version = std::make_unique<WidgetTextBox>(pt, bs);
  _widget_version->set_text("Kebb 1.2.0");
  _widget_version->set_color_text(kebb::color(kebb::ColorName::C_Yellow));

  char_size.set_scale(0.5);

  bs.w = char_size.w * 10;
  bs.h = char_size.h;
  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += bs.h * 2;
  _widget_date = std::make_unique<WidgetTextBox>(pt, bs);
  _widget_date->set_text("2023-08-29");
  _widget_date->set_color_text(kebb::color(kebb::ColorName::C_Yellow));

  char_size = _renderer->font_char_size(FontName::F_Menu);

  bs.w = char_size.w * 36;
  bs.h = char_size.h;
  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += bs.h * 4;
  _widget_github = std::make_unique<WidgetTextBox>(pt, bs);
  _widget_github->set_text("https://github.com/flinguenheld/kebb");
  _widget_github->set_color_text(kebb::color(kebb::ColorName::C_Teal));

  bs.w = char_size.w * 22;
  bs.h = char_size.h;
  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += bs.h * 2;
  _widget_email = std::make_unique<WidgetTextBox>(pt, bs);
  _widget_email->set_text("florent@linguenheld.fr");
  _widget_email->set_color_text(kebb::color(kebb::ColorName::C_Teal));
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
