#include "window_pause.h"
#include <memory>

WindowPause::WindowPause(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                         std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score)
    : WidgetWindow(next_window, renderer), _score(score) {

  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::FullScreen, screen_size, score, renderer);

  // ------------------------------------------------------------------------
  // Menu -------------------------------------------------------------------
  boxsize char_size = _renderer->char_size_menu();
  boxsize line_size = {static_cast<uint16_t>(char_size.w * 28), char_size.h};
  point pt = {static_cast<uint16_t>(screen_size.w / 2 - line_size.w / 2),
              static_cast<uint16_t>(screen_size.h - char_size.h * 2)};

  _widget_menu = std::make_unique<WidgetTextBox>(pt, line_size);
  _widget_menu->set_text("<ESC> Quit - <ENTER> Restart");
  _widget_menu->set_color_text({137, 180, 250, 200}); // Blue
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
  _widget_menu->render(_renderer->renderer(), _renderer->font_menu());

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}
