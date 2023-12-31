#include "window_welcome_timer.h"

WindowWelcomeTimer::WindowWelcomeTimer(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                                       std::shared_ptr<Renderer> renderer,
                                       std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window_id, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Go !");

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3.2);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 1.1;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Timer mode",
                                                  widget::color(widget::ColorName::C_Peach));
  pt.y += char_size.h * 1.5;

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.4);

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetList>(pt, char_size, "Countdown:",
                                   std::vector<SelectionItem>{{.text = "15s", .value_uint = 15},
                                                              {.text = "30s", .value_uint = 30},
                                                              {.text = "45s", .value_uint = 45},
                                                              {.text = "60s", .value_uint = 60},
                                                              {.text = "1m30", .value_uint = 90},
                                                              {.text = "2m", .value_uint = 120},
                                                              {.text = "2m30", .value_uint = 150},
                                                              {.text = "3m", .value_uint = 180},
                                                              {.text = "3m30", .value_uint = 210},
                                                              {.text = "4m", .value_uint = 240},
                                                              {.text = "4m30", .value_uint = 270},
                                                              {.text = "5m", .value_uint = 300},
                                                              {.text = "10m", .value_uint = 600}},
                                   true)); // Selected !
  _widget_select_fields.back()->set_choice_by_value(_options->get().timer_countdown);

  pt.y += char_size.h * 1.2;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, char_size, "Nb targets:", 1, 20, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get().timer_nb_targets);

  pt.y += char_size.h * 1.2;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, char_size, "Speed:", 1, 20, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get().timer_speed);
}

WindowWelcomeTimer::~WindowWelcomeTimer() {}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowWelcomeTimer::render() const {

  _renderer->clear_screen();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcomeTimer::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
void WindowWelcomeTimer::control_enter() {

  // Up options, save and launch the game !
  _options->set().timer_countdown = _widget_select_fields[0]->get_choice().value_uint;
  _options->set().timer_nb_targets = _widget_select_fields[1]->get_choice().value_uint;
  _options->set().timer_speed = _widget_select_fields[2]->get_choice().value_uint;
  _options->set().last_mode = uint16_t(kebb::GameMode::M_Timer);

  *_next_window_id = uint8_t(kebb::WindowName::W_GameTimer);
}
