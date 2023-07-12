
#include "window_welcome.h"

WindowWelcome::WindowWelcome(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                             std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window, renderer) {}

WindowWelcome::~WindowWelcome() {}

void WindowWelcome::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  // Reverse the timer
  // _widget_score->render(_score->seconds_until_stop());
  // _widget_menu->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}
