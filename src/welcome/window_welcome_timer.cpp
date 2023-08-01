#include "window_welcome_timer.h"
#include "option/option_file.h"

WindowWelcomeTimer::WindowWelcomeTimer(kebb::boxsize screen_size,
                                       std::shared_ptr<kebb::WindowName> next_window,
                                       std::shared_ptr<Renderer> renderer,
                                       std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Go !");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  kebb::boxsize bs_title;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3.5);
  bs_title.w = char_size.w * 9;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Timer mod");
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  const kebb::boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.5);
  const uint16_t y_space = bs_field.h * 1.2;

  pt.x = screen_size.w / 2;
  pt.y += bs_title.h * 2;

  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, bs_field, "Countdown:",
                                                                  std::vector<SelectionItem>{{"15s", "15"},
                                                                                             {"30s", "30"},
                                                                                             {"45s", "45"},
                                                                                             {"60s", "60"},
                                                                                             {"1m30", "90"},
                                                                                             {"2m", "120"},
                                                                                             {"2m30", "150"},
                                                                                             {"3m", "180"},
                                                                                             {"3m30", "210"},
                                                                                             {"4m", "240"},
                                                                                             {"4m30", "270"},
                                                                                             {"5m", "300"},
                                                                                             {"10m", "600"}},
                                                                  true)); // Selected !
  _widget_select_fields.back()->set_choice_by_value(_options->get(OptionName::Countdown));

  pt.y += y_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, bs_field, "Nb targets:", 1, 20, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get(OptionName::Targets));

  pt.y += y_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, bs_field, "Speed:",
                                                                  std::vector<SelectionItem>{{"1", "30"},
                                                                                             {"2", "28"},
                                                                                             {"3", "26"},
                                                                                             {"4", "24"},
                                                                                             {"5", "22"},
                                                                                             {"6", "20"},
                                                                                             {"7", "18"},
                                                                                             {"8", "16"},
                                                                                             {"9", "14"},
                                                                                             {"10", "12"},
                                                                                             {"11", "10"},
                                                                                             {"12", "8"},
                                                                                             {"13", "6"},
                                                                                             {"14", "4"},
                                                                                             {"15", "2"},
                                                                                             {"16", "1"}}));
  _widget_select_fields.back()->set_choice_by_value(_options->get(OptionName::Speed));
}

WindowWelcomeTimer::~WindowWelcomeTimer() {}

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
void WindowWelcomeTimer::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowWelcomeTimer::control_enter() {

  // Up options, save and launch the game !
  _options->set(OptionName::Countdown, _widget_select_fields[0]->get_choice().value);
  _options->set(OptionName::Targets, _widget_select_fields[1]->get_choice().value);
  _options->set(OptionName::Speed, _widget_select_fields[2]->get_choice().value);
  _options->set(OptionName::LastMod, "timer");
  _options->save();

  *_next_window = kebb::WindowName::W_GameTimer;
}
