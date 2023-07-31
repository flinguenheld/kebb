#include "window_welcome_survival.h"

WindowWelcomeSurvival::WindowWelcomeSurvival(kebb::boxsize screen_size,
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
  char_size.set_scale(3.2);
  bs_title.w = char_size.w * 12;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.8;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Survival mod");
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  const kebb::boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.4);
  const uint16_t y_space = bs_field.h * 1.4;

  pt.x = screen_size.w / 2;
  pt.y += bs_title.h * 2;

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetList>(pt, bs_field, "Difficulty:",
                                   std::vector<SelectionItem>{{"Very easy", "0"},
                                                              {"Easy", "1"},
                                                              {"Normal", "2"},
                                                              {"Hard", "3"},
                                                              {"Very hard", "4"},
                                                              {"Impossible", "5"}},
                                   true)); // Selected !
  _widget_select_fields.back()->set_choice_by_value(_options->get(OptionName::SurvivalDifficulty));
}

WindowWelcomeSurvival::~WindowWelcomeSurvival() {}

void WindowWelcomeSurvival::render() {

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
void WindowWelcomeSurvival::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowWelcomeSurvival::control_enter() {

  // Up options, save and launch the game !
  _options->set(OptionName::SurvivalDifficulty, _widget_select_fields[0]->get_choice().value);
  _options->set(OptionName::LastMod, "survival");
  _options->save();

  *_next_window = kebb::WindowName::W_GameSurvival;
}
