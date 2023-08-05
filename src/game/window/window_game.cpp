#include "window_game.h"

// clang-format off
WindowGame::WindowGame(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<RecordFile> records,
                       std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window, renderer),
      _score(score),
      _records(records),
      _options(options) {
  // clang-format on

  _dispatcher = std::make_shared<Dispatcher>(options);
  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::Top, screen_size, score, renderer);

  _nb_max_target = _dispatcher->number_of_chars() * 0.6; // Prevent the same targets/thread amount.

  // Geometry
  _target_center_aera = {static_cast<uint16_t>(screen_size.w / 2), static_cast<uint16_t>(screen_size.h / 2)};
  _target_radius_aera = int16_t(screen_size.w * 0.4);
}

WindowGame::~WindowGame() {}

void WindowGame::stop_threads() {

  for (auto &t : _targets) {
    t->stop();
  }
  for (auto &t : _threads) {
    t.join();
  }

  save_record(); // NOTE: Good here ?
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
/*
 * Call target renders and update screen.
 * Children have to clear the screen before calling this method.
 */
void WindowGame::render() const {

  for (auto &target : _targets)
    target->render(_renderer->renderer(), _renderer->font(FontName::F_Target));

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowGame::control_escape() {
  stop_threads();
  *_next_window = kebb::WindowName::W_Pause;
}
void WindowGame::control_others(uint16_t keycode) {

  // Loop in all targets, if ok, up the loop
  for (auto &target : _targets) {

    if (target->check_keycode(keycode))
      return;
  }

  _score->up_fail();
}
