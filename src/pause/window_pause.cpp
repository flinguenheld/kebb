#include "window_pause.h"

WindowPause::WindowPause(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                         std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score)
    : WidgetWindow(next_window, renderer), _score(score) {

  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::FullScreen, screen_size, score, renderer);
  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Restart");
}

WindowPause::~WindowPause() {}

void WindowPause::render() {

  _renderer->clear_screen();

  // Reverse the timer
  _widget_score->render(_score->seconds_until_stop());
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowPause::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowPause::control_enter() { *_next_window = kebb::WindowName::W_Game; }
