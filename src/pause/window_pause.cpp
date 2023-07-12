#include "window_pause.h"
#include "renderer.h"
#include "widget/widget_menu.h"
#include <memory>

WindowPause::WindowPause(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                         std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score)
    : WidgetWindow(next_window, renderer), _score(score) {

  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::FullScreen, screen_size, score, renderer);
  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Restart");
}

WindowPause::~WindowPause() {}

void WindowPause::control_escape() {
  *_next_window = WindowName::W_Quit; // TODO: Change to reception
}
void WindowPause::control_enter() { *_next_window = WindowName::W_Game; }

void WindowPause::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  // Reverse the timer
  _widget_score->render(_score->seconds_until_stop());
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}
