#include "window_welcome_survival.h"

WindowWelcomeSurvival::WindowWelcomeSurvival(widget::boxsize screen_size,
                                             std::shared_ptr<uint8_t> next_window_id,
                                             std::shared_ptr<Renderer> renderer,
                                             std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window_id, renderer), _options(options), _max_fail(1), _max_miss(1),
      _next_level(10) {

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
      std::vector<SelectionItem>{
          {.text = "Very easy", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_VeryEasy)},
          {.text = "Easy", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_Easy)},
          {.text = "Normal", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_Normal)},
          {.text = "Hard", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_Hard)},
          {.text = "Very hard", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_VeryHard)},
          {.text = "Impossible", .value_uint = uint16_t(kebb::SurvivalDifficulty::D_Impossible)}},
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
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(0.9);

  _widget_explanation_l1 = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "",
                                                           widget::color(widget::ColorName::C_Surface1));
  pt.y += char_size.h;
  _widget_explanation_l2 = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "",
                                                           widget::color(widget::ColorName::C_Surface1));
  pt.y += char_size.h;
  _widget_explanation_l3 = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "",
                                                           widget::color(widget::ColorName::C_Surface1));
}

WindowWelcomeSurvival::~WindowWelcomeSurvival() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::logic() {

  difficulty(_widget_select_fields[0]->get_choice().value_uint);

  _widget_explanation_l1->move_text(std::move("Next level with " + std::to_string(_next_level) + " points"));

  if (_widget_select_fields[0]->get_choice().value_uint == 10)
    _widget_explanation_l2->move_text(std::move("0 per fail & per miss"));
  else
    _widget_explanation_l2->move_text(std::move("-" + std::to_string(_cost_fail) + " per fail & -" +
                                                std::to_string(_cost_miss) + " per miss"));

  _widget_explanation_l3->move_text(
      std::move(std::to_string(_max_fail) + " fails & " + std::to_string(_max_miss) + " misses maximum"));
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
  _widget_explanation_l3->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
void WindowWelcomeSurvival::control_enter() {

  // Up options, save and launch the game !
  _options->set().survival_difficulty = _widget_select_fields[0]->get_choice().value_uint;
  _options->set().survival_max_fails = _max_fail;
  _options->set().survival_max_misses = _max_miss;
  _options->set().survival_next_level = _next_level;

  _options->set().survival_nb_targets = _widget_select_fields[1]->get_choice().value_uint;
  _options->set().survival_speed = _widget_select_fields[2]->get_choice().value_uint;

  _options->set().last_mode = uint16_t(kebb::GameMode::M_Survival);

  *_next_window_id = uint8_t(kebb::WindowName::W_GameSurvival);
}

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------
void WindowWelcomeSurvival::difficulty(uint16_t difficulty) {

  switch (difficulty) {

  case uint16_t(kebb::SurvivalDifficulty::D_VeryEasy):
    _max_fail = 25;
    _max_miss = 50;

    _cost_fail = 0;
    _cost_miss = 0;

    _next_level = 20;
    break;
  case uint16_t(kebb::SurvivalDifficulty::D_Easy):
    _max_fail = 20;
    _max_miss = 30;

    _cost_fail = 1;
    _cost_miss = 1;

    _next_level = 30;
    break;
  case uint16_t(kebb::SurvivalDifficulty::D_Normal):
    _max_fail = 15;
    _max_miss = 20;

    _cost_fail = 2;
    _cost_miss = 1;

    _next_level = 35;
    break;
  case uint16_t(kebb::SurvivalDifficulty::D_Hard):
    _max_fail = 10;
    _max_miss = 15;

    _cost_fail = 4;
    _cost_miss = 2;

    _next_level = 40;
    break;
  case uint16_t(kebb::SurvivalDifficulty::D_VeryHard):
    _max_fail = 5;
    _max_miss = 10;

    _cost_fail = 6;
    _cost_miss = 3;

    _next_level = 50;
    break;
  default: // Impossible
    _max_fail = 2;
    _max_miss = 5;

    _cost_fail = 10;
    _cost_miss = 5;

    _next_level = 60;
  }
}
