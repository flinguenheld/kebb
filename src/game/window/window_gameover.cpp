#include "window_gameover.h"
#include "utils.h"

WindowGameOver::WindowGameOver(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                               std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records,
                               std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window, renderer), _records(records), _options(options) {

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::boxsize bs;
  kebb::point pt;

  if (_records->records().empty()) {

    // FIX: Add a message ??
    std::cout << "records is empty !!!!!!!" << std::endl;

  } else {

    // ------------------------------------------------------------------------
    // Title ------------------------------------------------------------------
    std::string title;
    SDL_Color title_color;

    switch ((kebb::GameStatus)_records->records()[0].status) {

    case kebb::GameStatus::S_Win:
      title = "You win";
      title_color = kebb::color(kebb::ColorName::C_Green);
      break;
    case kebb::GameStatus::S_Loose:
      title = "You loose";
      title_color = kebb::color(kebb::ColorName::C_Red);
      break;
    case kebb::GameStatus::S_TimeUp:
      title = "Time's up";
      title_color = kebb::color(kebb::ColorName::C_Green);
      break;
    default:
      title = "Quit";
      title_color = kebb::color(kebb::ColorName::C_Sky);
    }
    char_size.set_scale(3);
    bs.w = char_size.w * title.length();
    bs.h = char_size.h;

    pt.x = screen_size.w / 2 - bs.w / 2;
    pt.y = bs.h * 0.2;

    _textbox_title = std::make_unique<WidgetTextBox>(pt, bs);
    _textbox_title->set_text(std::move(title));
    _textbox_title->set_color_text(std::move(title_color));

    pt.y += bs.h * 1.3;

    // ------------------------------------------------------------------------
    // Separation -------------------------------------------------------------
    _separation_color = kebb::color(kebb::ColorName::C_Overlay0);
    _separation_color.a = 40;

    _separation_0.w = screen_size.w / 2;
    _separation_0.h = char_size.h / 10;
    _separation_0.x = screen_size.w / 2 - _separation_0.w / 2;
    _separation_0.y = pt.y;

    pt.y += _separation_0.h * 2;

    // ------------------------------------------------------------------------
    // Mod --------------------------------------------------------------------
    std::string mod;
    if ((kebb::GameMod)_records->records()[0].mod == kebb::GameMod::M_Survival)
      mod = "Survival mod";
    else
      mod = "Timer mod";

    char_size = _renderer->font_char_size(FontName::F_Menu);
    char_size.set_scale(1.3);
    bs.w = char_size.w * mod.length();
    bs.h = char_size.h;

    pt.x = screen_size.w / 2 - bs.w / 2;
    pt.y += bs.h * 0.05;

    _textbox_mod = std::make_unique<WidgetTextBox>(pt, bs);
    _textbox_mod->set_text(std::move(mod));
    _textbox_mod->set_color_text(kebb::color(kebb::ColorName::C_Text));

    pt.y += bs.h;

    // ------------------------------------------------------------------------
    // Difficulty -------------------------------------------------------------
    std::string difficulty;
    if ((kebb::GameMod)_records->records()[0].mod == kebb::GameMod::M_Survival) {
      switch (_records->records()[0].difficulty) {
      case 0:
        difficulty += "Very easy";
        break;
      case 1:
        difficulty += "Easy";
        break;
      case 2:
        difficulty += "Normal";
        break;
      case 3:
        difficulty += "Hard";
        break;
      case 4:
        difficulty += "Very hard";
        break;
      default:
        difficulty += "Impossible";
      }
    } else {
      difficulty = std::to_string(_records->records()[0].nb_target) + " targets - speed " +
                   kebb::speed(_records->records()[0].speed);
    }

    char_size = _renderer->font_char_size(FontName::F_Menu);
    char_size.set_scale(1.2);
    bs.w = char_size.w * difficulty.length();
    bs.h = char_size.h;

    pt.x = screen_size.w / 2 - bs.w / 2;
    pt.y += bs.h * 0.05;

    _textbox_difficulty = std::make_unique<WidgetTextBox>(pt, bs);
    _textbox_difficulty->set_text(std::move(difficulty));
    _textbox_difficulty->set_color_text(kebb::color(kebb::ColorName::C_Text));

    pt.y += bs.h * 1.5;
  }

  // ------------------------------------------------------------------------
  // Separation -------------------------------------------------------------
  _separation_1 = _separation_0;
  _separation_1.y = pt.y;

  pt.y += _separation_1.h * 2;

  // ------------------------------------------------------------------------
  // Timer ------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu);

  char_size.set_scale(2.4);
  bs.w = char_size.w * 5;
  bs.h = char_size.h;

  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += char_size.h * 0.05;

  _textbox_time = std::make_unique<WidgetTextBox>(pt, bs);
  _textbox_time->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  pt.y += bs.h * 1.1;

  // ------------------------------------------------------------------------
  // Success / Fail / Miss --------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu);
  char_size.set_scale(1.5);

  bs.w = char_size.w * 13; // 13 chars in total for all lines to align
  bs.h = char_size.h;

  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y += bs.h * 0.05;

  _textbox_success = std::make_unique<WidgetTextBox>(pt, bs);
  pt.y += char_size.h;
  _textbox_fail = std::make_unique<WidgetTextBox>(pt, bs);
  pt.y += char_size.h;
  _textbox_miss = std::make_unique<WidgetTextBox>(pt, bs);

  _textbox_success->set_color_text(kebb::color(kebb::ColorName::C_Blue));
  _textbox_fail->set_color_text(kebb::color(kebb::ColorName::C_Blue));
  _textbox_miss->set_color_text(kebb::color(kebb::ColorName::C_Blue));

  _textbox_success->set_text("Success " +
                             kebb::adapt_string_length(std::to_string(_records->records()[0].success), 5));
  _textbox_fail->set_text("Fail " +
                          kebb::adapt_string_length(std::to_string(_records->records()[0].fail), 8));
  _textbox_miss->set_text("Miss " +
                          kebb::adapt_string_length(std::to_string(_records->records()[0].miss), 8));

  int t = _records->records()[0].time_game;
  _textbox_time->set_text(kebb::adapt_string_length(std::to_string(t / 60), 2, '0') + ":" +
                          kebb::adapt_string_length(std::to_string(t % 60), 2, '0'));

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

  _textbox_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_mod->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_difficulty->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _textbox_time->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_success->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_fail->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _textbox_miss->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

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
void WindowGameOver::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowGameOver::control_enter() {
  if (_options->get().last_mod == uint16_t(kebb::GameMod::M_Timer))
    *_next_window = kebb::WindowName::W_GameTimer;
  else
    *_next_window = kebb::WindowName::W_GameSurvival;
}
