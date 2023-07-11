#include "window_pause.h"

WindowPause::WindowPause(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<WindowName> next_window,
                         std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score)
    : WidgetWindow(next_window, renderer), _score(score) {}
WindowPause::~WindowPause() {

  // title_char_size({static_cast<uint16_t>(_target_font_size * 0.6),
  //                    static_cast<uint16_t>(_target_font_size * 1.15)}),
}

void WindowPause::control_escape() {
  *_next_window = WindowName::W_Quit; // TODO: Change to reception
}
void WindowPause::control_enter() {}
void WindowPause::control_up() { std::cout << "Up from WindowPause" << std::endl; }
void WindowPause::control_down() { std::cout << "Down from WindowPause" << std::endl; }

void WindowPause::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  _score->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}
