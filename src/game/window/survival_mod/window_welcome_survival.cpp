#include "window_welcome_survival.h"
#include "renderer.h"
#include <cmath>

WindowWelcomeSurvival::WindowWelcomeSurvival(kebb::boxsize screen_size,
                                             std::shared_ptr<kebb::WindowName> next_window,
                                             std::shared_ptr<Renderer> renderer,
                                             std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Go !");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::boxsize bs_title;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3.2);
  bs_title.w = char_size.w * 12;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.5;

  _textbox_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _textbox_title->set_text("Survival mod");
  _textbox_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  kebb::boxsize bs = renderer->font_char_size(FontName::F_Menu).scale(1.5);
  const uint16_t y_space = bs.h * 1.2;

  pt.x = screen_size.w / 2;
  pt.y += bs_title.h * 2;

  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, bs, "Nb targets:", 2, 15, 1, true));
  _widget_select_fields.back()->set_choice_by_value(_options->get().survival_nb_targets);

  pt.y += y_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, bs, "Speed", 1, 15, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get().survival_speed);

  pt.y += y_space * 1.8;

  // ------------------------------------------------------------------------
  // Explanations -----------------------------------------------------------
  std::string explanation_l1 = "Select starting options and try";
  std::string explanation_l2 = "to reach the twelfth level !";

  char_size = _renderer->font_char_size(FontName::F_Menu);
  bs.h = char_size.h;

  bs.w = char_size.w * explanation_l1.length();
  pt.x = screen_size.w / 2 - bs.w / 2;

  _textbox_explanation_l1 = std::make_unique<WidgetTextBox>(pt, bs);
  _textbox_explanation_l1->set_text(std::move(explanation_l1));
  _textbox_explanation_l1->set_color_text(kebb::color(kebb::ColorName::C_Overlay1));

  pt.y += bs.h;
  bs.w = char_size.w * explanation_l2.length();
  pt.x = screen_size.w / 2 - bs.w / 2;

  _textbox_explanation_l2 = std::make_unique<WidgetTextBox>(pt, bs);
  _textbox_explanation_l2->set_text(std::move(explanation_l2));
  _textbox_explanation_l2->set_color_text(kebb::color(kebb::ColorName::C_Overlay1));
}

WindowWelcomeSurvival::~WindowWelcomeSurvival() {}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::render() const {

  _renderer->clear_screen();
  _textbox_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _textbox_explanation_l1->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_explanation_l2->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowWelcomeSurvival::control_enter() {

  // Up options, save and launch the game !
  _options->set().survival_nb_targets = _widget_select_fields[0]->get_choice().value_uint;
  _options->set().survival_speed = _widget_select_fields[1]->get_choice().value_uint;
  _options->set().last_mod = uint16_t(kebb::GameMod::M_Survival);

  *_next_window = kebb::WindowName::W_GameSurvival;
}
