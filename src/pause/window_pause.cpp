#include "window_pause.h"
#include "option/option_file.h"

WindowPause::WindowPause(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                         std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                         std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window, renderer), _score(score), _options(options) {

  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::FullScreen, screen_size, score, renderer);
  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Restart");
}

WindowPause::~WindowPause() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowPause::logic() { _widget_score->logic(_score->seconds_until_stop()); }

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowPause::render() const {

  _renderer->clear_screen();

  // Reverse the timer
  _widget_score->render();
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowPause::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowPause::control_enter() {
  if (_options->get(OptionName::LastMod) == "timer")
    *_next_window = kebb::WindowName::W_GameTimer;
  else
    *_next_window = kebb::WindowName::W_GameSurvival;
}
