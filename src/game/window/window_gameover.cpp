#include "window_gameover.h"
#include "renderer.h"
#include "utils.h"
#include "widget/widget_textbox.h"
#include <memory>

WindowGameOver::WindowGameOver(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                               std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                               std::shared_ptr<RecordFile> records, std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window, renderer), _score(score), _records(records), _options(options) {

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  kebb::boxsize bs_title;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  std::string title;
  SDL_Color color;
  if (!_records->records().empty()) { // FIX: Check if records are empty or add an empty record ?

    switch ((kebb::GameStatus)_records->records()[0].status) {

    case kebb::GameStatus::S_Win:
      title = "You win";
      color = kebb::color(kebb::ColorName::C_Green);
      break;
    case kebb::GameStatus::S_Loose:
      title = "You loose";
      color = kebb::color(kebb::ColorName::C_Red);
      break;
    case kebb::GameStatus::S_TimeUp:
      title = "Time's up";
      color = kebb::color(kebb::ColorName::C_Sky);
      break;
    default:
      title = "Quit";
      color = kebb::color(kebb::ColorName::C_Blue);
    }
  }
  char_size.set_scale(3);
  bs_title.w = char_size.w * title.length();
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text(std::move(title));
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::FullScreen, screen_size, score, renderer);
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

  // Reverse the timer
  // _widget_score->render();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Score));
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
