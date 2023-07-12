#include "window_welcome.h"

WindowWelcome::WindowWelcome(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                             std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Valid");
}

WindowWelcome::~WindowWelcome() {}

void WindowWelcome::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcome::control_escape() { *_next_window = WindowName::W_Quit; }
void WindowWelcome::control_enter() {
  *_next_window = WindowName::W_Game;
} // TODO: Change according to selection
