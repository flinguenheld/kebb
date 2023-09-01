#include "window_gameover.h"

WindowGameOver::WindowGameOver(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                               std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records,
                               std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window_id, renderer), _records(records), _options(options) {

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  if (_records->records().empty()) {

    // TODO: Add a message (Cannot be empty) ??
    std::cout << "Record file is empty !" << std::endl;

  } else {

    // ------------------------------------------------------------------------
    // Title ------------------------------------------------------------------
    std::string title;
    SDL_Color title_color;

    switch ((kebb::GameStatus)_records->records()[0].status) {

    case kebb::GameStatus::S_Win:
      title = "You win";
      title_color = widget::color(widget::ColorName::C_Green);
      break;
    case kebb::GameStatus::S_Loose:
      title = "You loose";
      title_color = widget::color(widget::ColorName::C_Red);
      break;
    case kebb::GameStatus::S_TimeUp:
      title = "Time's up";
      title_color = widget::color(widget::ColorName::C_Green);
      break;
    default:
      title = "Quit";
      title_color = widget::color(widget::ColorName::C_Sky);
    }
    char_size.set_scale(3);

    const uint16_t space(char_size.h * 0.6);

    pt.x = screen_size.w / 2;
    pt.y += char_size.h * 0.7;
    _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, std::move(title),
                                                    widget::color(widget::ColorName::C_Peach));
    pt.y += space;

    // ------------------------------------------------------------------------
    // Separation -------------------------------------------------------------
    _separation_color = widget::color(widget::ColorName::C_Overlay0);
    _separation_color.a = 40;

    _separation_0.w = screen_size.w / 2;
    _separation_0.h = char_size.h / 10;
    _separation_0.x = screen_size.w / 2 - _separation_0.w / 2;
    _separation_0.y = pt.y;

    pt.y += space;

    // ------------------------------------------------------------------------
    // Mode -------------------------------------------------------------------
    std::string mode;
    if ((kebb::GameMode)_records->records()[0].mode == kebb::GameMode::M_Survival)
      mode = "Survival mode";
    else
      mode = "Timer mode";

    char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.3);
    _widget_mode = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, std::move(mode),
                                                   widget::color(widget::ColorName::C_Text));
    pt.y += char_size.h;

    // ------------------------------------------------------------------------
    // Difficulty -------------------------------------------------------------
    std::string difficulty;
    if ((kebb::GameMode)_records->records()[0].mode == kebb::GameMode::M_Survival) {

      if (_records->records()[0].survival_speed + _records->records()[0].survival_nb_targets < 5)
        difficulty += "Very easy";
      else if (_records->records()[0].survival_speed + _records->records()[0].survival_nb_targets < 10)
        difficulty += "Easy";
      else if (_records->records()[0].survival_speed + _records->records()[0].survival_nb_targets < 15)
        difficulty += "Normal";
      else if (_records->records()[0].survival_speed + _records->records()[0].survival_nb_targets < 20)
        difficulty += "Hard";
      else if (_records->records()[0].survival_speed + _records->records()[0].survival_nb_targets < 25)
        difficulty += "Very hard";
      else
        difficulty += "Impossible";

      difficulty += " (" + std::to_string(_records->records()[0].survival_nb_targets) + "/" +
                    std::to_string(_records->records()[0].survival_speed) + ")";
    } else {
      difficulty = std::to_string(_records->records()[0].timer_nb_target) + " targets - speed " +
                   std::to_string(_records->records()[0].timer_speed);
    }

    char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.2);

    _widget_difficulty =
        std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, std::move(difficulty),
                                        widget::color(widget::ColorName::C_Text));
    pt.y += space * 0.8;

    // ------------------------------------------------------------------------
    // Separation -------------------------------------------------------------
    _separation_1 = _separation_0;
    _separation_1.y = pt.y;
    pt.y += space;

    // ------------------------------------------------------------------------
    // Timer ------------------------------------------------------------------
    int t = _records->records()[0].time_game;
    char_size = _renderer->font_char_size(FontName::F_Menu).scale(2.3);

    _widget_time =
        std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center,
                                        widget::adapt_string_length(std::to_string(t / 60), 2, '0') + ":" +
                                            widget::adapt_string_length(std::to_string(t % 60), 2, '0'),
                                        widget::color(widget::ColorName::C_Peach));
    pt.y += char_size.h;

    // ------------------------------------------------------------------------
    // Success / Fail / Miss --------------------------------------------------
    char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.2);

    _widget_success = std::make_unique<WidgetTextBox>(
        pt, char_size, TextBoxAlign::TB_Center,
        "Success " + widget::adapt_string_length(std::to_string(_records->records()[0].success), 5),
        widget::color(widget::ColorName::C_Blue));
    pt.y += char_size.h;
    _widget_fail = std::make_unique<WidgetTextBox>(
        pt, char_size, TextBoxAlign::TB_Center,
        "Fail " + widget::adapt_string_length(std::to_string(_records->records()[0].fail), 8),
        widget::color(widget::ColorName::C_Blue));
    pt.y += char_size.h;
    _widget_miss = std::make_unique<WidgetTextBox>(
        pt, char_size, TextBoxAlign::TB_Center,
        "Miss " + widget::adapt_string_length(std::to_string(_records->records()[0].miss), 8),
        widget::color(widget::ColorName::C_Blue));
  }
  // ------------------------------------------------------------------------
  // Menu -------------------------------------------------------------------
  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Restart");
}

WindowGameOver::~WindowGameOver() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowGameOver::logic() {
  // _widget_score->logic(_score->seconds_until_stop());
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowGameOver::render() const {

  _renderer->clear_screen();

  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_mode->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_difficulty->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_time->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_success->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_fail->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_miss->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  // --
  SDL_SetRenderDrawColor(_renderer->renderer(), _separation_color.r, _separation_color.g, _separation_color.b,
                         _separation_color.a);
  SDL_RenderFillRect(_renderer->renderer(), &_separation_0);
  SDL_RenderFillRect(_renderer->renderer(), &_separation_1);

  // --
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowGameOver::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
void WindowGameOver::control_enter() {
  if (_options->get().last_mode == uint16_t(kebb::GameMode::M_Timer))
    *_next_window_id = uint8_t(kebb::WindowName::W_GameTimer);
  else
    *_next_window_id = uint8_t(kebb::WindowName::W_GameSurvival);
}
