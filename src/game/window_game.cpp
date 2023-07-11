#include "window_game.h"
#include "renderer.h"
#include "widget/widget_window.h"
#include <memory>

// clang-format off
WindowGame::WindowGame(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                       std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score)
    : WidgetWindow(next_window, renderer),
      _target_center_aera({static_cast<uint16_t>(screen_size.w / 2),
                           static_cast<uint16_t>(screen_size.h / 2)}),
      _target_radius_aera(int16_t(screen_size.w * 0.4)),
      _score(score) {
  // clang-format on

  _dispatcher = std::make_shared<Dispatcher>();
  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::Top, screen_size, score, renderer);

  // TODO: Move to easily start/restart according to options or just delete the window ?
  for (uint8_t i = 0; i < 5; ++i)
    _targets.emplace_back(
        Target(_target_center_aera, _target_radius_aera, _renderer->char_size_target(), _dispatcher, _score));

  // Start !
  for (auto &t : _targets) {
    _threads.emplace_back(std::thread(&Target::update, &t));
  }
}
WindowGame::~WindowGame() {}

void WindowGame::stop_threads() {

  for (auto &t : _targets) {
    t.stop();
  }
  for (auto &t : _threads) {
    t.join();
  }
}

// ----------------------------------------------------------------------------------------------------
// CONTROLER ------------------------------------------------------------------------------------------
void WindowGame::control_escape() {

  stop_threads();
  *_next_window = WindowName::W_Pause;

  // TODO: message to ??
}
void WindowGame::control_others(uint16_t keycode) {

  // Loop in all targets, if ok, up the loop
  for (auto &target : _targets) {

    if (target.check_keycode(keycode))
      return;
  }

  _score->up_fail();
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowGame::render() {
  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  // _score->render();
  _widget_score->render();

  for (auto &target : _targets)
    target.render(_renderer->renderer(), _renderer->font_target());

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}
