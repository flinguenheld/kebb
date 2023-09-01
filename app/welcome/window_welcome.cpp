#include "window_welcome.h"

WindowWelcome::WindowWelcome(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                             std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window_id, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Valid");

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(5);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Kebb",
                                                  widget::color(widget::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Logo -------------------------------------------------------------------
  widget::boxsize bs_logo = {static_cast<uint16_t>(screen_size.w / 3),
                             static_cast<uint16_t>(screen_size.w / 7.5)};
  pt.x = screen_size.w / 2 - bs_logo.w / 2;
  pt.y += char_size.h * 0.5;

  _widget_logo = std::make_shared<WidgetLogo>(pt, bs_logo);
  _thread = std::thread(&WidgetLogo::update, _widget_logo);

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.6);
  pt.x = screen_size.w / 2;
  pt.y += bs_logo.h * 1.7;

  // Set the current selection based on the last game
  bool first_sel = _options->get().last_mode == uint16_t(kebb::GameMode::M_Survival);

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetSelection>(pt, char_size, "Survival mode", first_sel));
  pt.y += char_size.h * 1.1;
  _widget_select_fields.emplace_back(
      std::make_unique<WidgetSelection>(pt, char_size, "Timer mode", !first_sel));
  pt.y += char_size.h * 1.3;

  char_size = renderer->font_char_size(FontName::F_Menu).scale(1.3);
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, char_size, "Options"));
  pt.y += char_size.h * 1.1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, char_size, "Records"));
  pt.y += char_size.h * 1.1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, char_size, "About"));
}

WindowWelcome::~WindowWelcome() {
  _widget_logo->stop();
  _thread.join();
}

void WindowWelcome::render() const {

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
void WindowWelcome::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Quit); }
void WindowWelcome::control_enter() {

  if (_widget_select_fields[0]->is_selected())
    *_next_window_id = uint8_t(kebb::WindowName::W_WelcomeSurvival);
  else if (_widget_select_fields[1]->is_selected())
    *_next_window_id = uint8_t(kebb::WindowName::W_WelcomeTimer);
  else if (_widget_select_fields[2]->is_selected())
    *_next_window_id = uint8_t(kebb::WindowName::W_Option);
  else if (_widget_select_fields[3]->is_selected())
    *_next_window_id = uint8_t(kebb::WindowName::W_Record);
  else if (_widget_select_fields[4]->is_selected())
    *_next_window_id = uint8_t(kebb::WindowName::W_About);
}
