#include "window_pause.h"

WindowPause::WindowPause(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<WindowName> next_window,
                         std::shared_ptr<Score> score)
    : WidgetWindow(next_window), _score(score) {}
WindowPause::~WindowPause() {}

void WindowPause::control_escape() {
  *_next_window = WindowName::W_Quit; // TODO: Change to reception
}
void WindowPause::control_enter() {}
void WindowPause::control_up() { std::cout << "Up from WindowPause" << std::endl; }
void WindowPause::control_down() { std::cout << "Down from WindowPause" << std::endl; }

void WindowPause::render(std::shared_ptr<Renderer> renderer) {

  // Clear screen
  SDL_SetRenderDrawColor(renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(renderer->renderer());

  _score->render(renderer->renderer(), renderer->font_score());

  // Update Screen
  SDL_RenderPresent(renderer->renderer());
}
