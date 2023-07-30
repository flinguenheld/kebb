#include "window_welcome.h"
#include "option/option_file.h"
#include "widget/button/widget_list.h"

WindowWelcome::WindowWelcome(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                             std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Valid");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  kebb::boxsize bs_title;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(5);
  bs_title.w = char_size.w * 4;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Kebb");
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Logo -------------------------------------------------------------------
  kebb::boxsize bs_logo = {static_cast<uint16_t>(screen_size.w / 3),
                           static_cast<uint16_t>(screen_size.w / 7.5)};
  pt.x = screen_size.w / 2 - bs_logo.w / 2;
  pt.y += bs_title.h * 1.05;

  _widget_logo = std::make_shared<WidgetLogo>(pt, bs_logo);
  _thread = std::thread(&WidgetLogo::update, _widget_logo);

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  kebb::boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.6);
  pt.x = screen_size.w / 2;
  pt.y += bs_logo.h * 1.7;

  // Set the current selection based on the last game
  bool select_timer = false, select_survival = false;
  (_options->get(OptionName::LastMod) == "timer") ? select_timer = true : select_survival = true;

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetSelection>(pt, bs_field, "Timer mod", select_timer));
  pt.y += bs_field.h * 1.1;
  _widget_select_fields.emplace_back(
      std::make_unique<WidgetSelection>(pt, bs_field, "Survival mod", select_survival));
  pt.y += bs_field.h * 1.5;

  bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.4);
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, bs_field, "Options"));
  pt.y += bs_field.h * 1.1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, bs_field, "About"));
}

WindowWelcome::~WindowWelcome() {
  _widget_logo->stop();
  _thread.join();
}

void WindowWelcome::render() {

  _renderer->clear_screen();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_logo->render(_renderer->renderer());

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcome::control_escape() { *_next_window = kebb::WindowName::W_Quit; }
void WindowWelcome::control_enter() {

  if (_widget_select_fields[0]->is_selected())
    *_next_window = kebb::WindowName::W_WelcomeTimer;
  else if (_widget_select_fields[1]->is_selected())
    *_next_window = kebb::WindowName::W_WelcomeSurvival;
  else if (_widget_select_fields[2]->is_selected())
    *_next_window = kebb::WindowName::W_Option;
  else if (_widget_select_fields[3]->is_selected())
    *_next_window = kebb::WindowName::W_About;
}
