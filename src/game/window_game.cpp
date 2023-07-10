#include "window_game.h"

// clang-format off
WindowGame::WindowGame(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<Score> score)
    : _target_center_aera({static_cast<uint16_t>(screen_size.w * scale_factor / 2),
                           static_cast<uint16_t>(screen_size.h * scale_factor / 2)}),
      _target_radius_aera(int16_t(screen_size.w * scale_factor * 0.4)),
      _target_font_size(uint16_t(_target_radius_aera * 0.18)),
      _target_char_size({static_cast<uint16_t>(_target_font_size * 0.6),
                         static_cast<uint16_t>(_target_font_size * 1.15)}),
      _score(score) {
  // clang-format on

  _dispatcher = std::make_shared<Dispatcher>();

  // TODO: Move to easily start/restart according to options or just delete the window ?
  for (uint8_t i = 0; i < 5; ++i)
    _targets.emplace_back(
        Target(_target_center_aera, _target_radius_aera, _target_char_size, _dispatcher, _score));
}

void WindowGame::start_threads() {

  for (auto &t : _targets) {
    _threads.emplace_back(std::thread(&Target::update, &t));
  }
}
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
void WindowGame::render(SDL_Renderer *_renderer, TTF_Font *font_target, TTF_Font *font_score) {
  // Clear screen
  SDL_SetRenderDrawColor(_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer);

  _score->render(_renderer, font_score);

  for (auto &target : _targets)
    target.render(_renderer, font_target);

  // Update Screen
  SDL_RenderPresent(_renderer);
}
