#include "window_game.h"
#include "SDL_ttf.h"
#include "renderer.h"

WindowGame::WindowGame(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<Score> score)
    : target_center_aera({static_cast<uint16_t>(screen_size.w * scale_factor / 2),
                          static_cast<uint16_t>(screen_size.h * scale_factor / 2)}),
      target_radius_aera(int16_t(screen_size.w * scale_factor * 0.4)),
      target_font_size(uint16_t(target_radius_aera * 0.18)),
      target_char_size(
          {static_cast<uint16_t>(target_font_size * 0.6), static_cast<uint16_t>(target_font_size * 1.15)}),
      _score(score) {

  _dispatcher = std::make_shared<Dispatcher>();

  // TODO: Move to easily start/restart according to options
  for (uint8_t i = 0; i < 5; ++i)
    _targets.emplace_back(
        Target(target_center_aera, target_radius_aera, target_char_size, _dispatcher, _score));
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

void WindowGame::controller() {}

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
