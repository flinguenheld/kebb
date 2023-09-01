#include "window_welcome_survival.h"
#include <cstdint>

WindowWelcomeSurvival::WindowWelcomeSurvival(widget::boxsize screen_size,
                                             std::shared_ptr<uint8_t> next_window_id,
                                             std::shared_ptr<Renderer> renderer,
                                             std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window_id, renderer), _options(options) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Go !");

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3.1);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 1.1;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Survival mode",
                                                  widget::color(widget::ColorName::C_Peach));
  pt.y += char_size.h * 1.5;

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.3);

  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(
      pt, char_size, "Difficulty:",
      std::vector<SelectionItem>{{.text = "Very easy", .value_string = "Very easy"},
                                 {.text = "Easy", .value_string = "Easy"},
                                 {.text = "Normal", .value_string = "Normal"},
                                 {.text = "Hard", .value_string = "Hard"},
                                 {.text = "Very hard", .value_string = "Very hard"},
                                 {.text = "Impossible", .value_string = "Impossible"}},
      true)); // Selected !
  _widget_select_fields.back()->set_choice_by_value(_options->get().survival_difficulty);

  pt.y += char_size.h * 1.2;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, char_size, "Nb targets:", 2, 15, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get().survival_nb_targets);

  pt.y += char_size.h * 1.2;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(pt, char_size, "Speed:", 1, 15, 1));
  _widget_select_fields.back()->set_choice_by_value(_options->get().survival_speed);

  pt.y += char_size.h * 2;

  // ------------------------------------------------------------------------
  // Explanations -----------------------------------------------------------
  // FIX: INCOMPLETE
  char_size = _renderer->font_char_size(FontName::F_Menu);

  _widget_explanation_l1 = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center,
                                                           "Select starting options and try",
                                                           widget::color(widget::ColorName::C_Overlay1));
  pt.y += char_size.h;
  _widget_explanation_l2 =
      std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "to reach the twelfth level !",
                                      widget::color(widget::ColorName::C_Overlay1));
}

WindowWelcomeSurvival::~WindowWelcomeSurvival() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::logic() {

  _widget_explanation_l2->move_text(
      std::move("Next level with " + std::to_string(next_level("Normal")) + " points."));
  _widget_explanation_l2->move_text(std::move(std::to_string(max_fail("Normal")) + " fail & " +
                                              std::to_string(max_miss("Normal")) + " misses maximum"));
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::render() const {

  _renderer->clear_screen();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_explanation_l1->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_explanation_l2->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
void WindowWelcomeSurvival::control_enter() {

  // Up options, save and launch the game !
  _options->set().survival_difficulty = _widget_select_fields[0]->get_choice().value_string;
  _options->set().survival_max_fail = max_fail(_widget_select_fields[0]->get_choice().value_string);
  _options->set().survival_max_miss = max_miss(_widget_select_fields[0]->get_choice().value_string);
  _options->set().survival_next_level = next_level(_widget_select_fields[0]->get_choice().value_string);

  _options->set().survival_nb_targets = _widget_select_fields[1]->get_choice().value_uint;
  _options->set().survival_speed = _widget_select_fields[2]->get_choice().value_uint;

  _options->set().last_mode = uint16_t(kebb::GameMode::M_Survival);

  *_next_window_id = uint8_t(kebb::WindowName::W_GameSurvival);
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
uint16_t WindowWelcomeSurvival::max_fail(const std::string &difficulty) {

  if (_options->get().survival_difficulty == "Very easy")
    return 10;
  else if (_options->get().survival_difficulty == "Easy")
    return 10;
  else if (_options->get().survival_difficulty == "Normal")
    return 10;
  else if (_options->get().survival_difficulty == "Hard")
    return 10;
  else if (_options->get().survival_difficulty == "Very hard")
    return 10;
  else
    return 10;
}
uint16_t WindowWelcomeSurvival::max_miss(const std::string &difficulty) {

  if (_options->get().survival_difficulty == "Very easy")
    return 10;
  else if (_options->get().survival_difficulty == "Easy")
    return 10;
  else if (_options->get().survival_difficulty == "Normal")
    return 10;
  else if (_options->get().survival_difficulty == "Hard")
    return 10;
  else if (_options->get().survival_difficulty == "Very hard")
    return 10;
  else
    return 10;
}
uint16_t WindowWelcomeSurvival::next_level(const std::string &difficulty) {

  if (_options->get().survival_difficulty == "Very easy")
    return 10;
  else if (_options->get().survival_difficulty == "Easy")
    return 10;
  else if (_options->get().survival_difficulty == "Normal")
    return 10;
  else if (_options->get().survival_difficulty == "Hard")
    return 10;
  else if (_options->get().survival_difficulty == "Very hard")
    return 10;
  else
    return 10;
}
