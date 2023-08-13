#include "window_game.h"
#include "file/layout_file.h"

// clang-format off
WindowGame::WindowGame(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<RecordFile> records,
                       std::shared_ptr<OptionFile> options,
                       std::shared_ptr<LayoutFile> layouts)
    : WidgetWindow(next_window, renderer),
      _records(records),
      _options(options),
      _layouts(layouts),
      _game_status(kebb::GameStatus::S_Quit) {
  // clang-format on

  _dispatcher = std::make_shared<Dispatcher>(options, layouts);
  _nb_max_target = _dispatcher->number_of_chars() * 0.6; // Prevent the same targets/thread amount.

  _score = std::make_shared<Score>();
  _widget_score = std::make_unique<WidgetScore>(screen_size, _score, renderer);

  // Geometry
  _target_center_aera = {static_cast<uint16_t>(screen_size.w / 2), static_cast<uint16_t>(screen_size.h / 2)};
  _target_radius_aera = int16_t(screen_size.w * 0.4);
}

WindowGame::~WindowGame() {}

void WindowGame::stop_game() {

  for (auto &t : _targets) {
    t->stop();
  }
  for (auto &t : _threads) {
    t.join();
  }

  save_record();
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
  stop_game();
  *_next_window = kebb::WindowName::W_GameOver;
}
void WindowGame::control_others(const std::string &character) {

  // Loop in all targets, if ok, up the loop
  for (auto &target : _targets) {

    if (target->check_key(character))
      return;
  }

  _score->up_fail();
}
