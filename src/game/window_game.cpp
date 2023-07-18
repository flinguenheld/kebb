#include "window_game.h"
#include "option/option_file.h"
#include <string>

// clang-format off
WindowGame::WindowGame(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WidgetWindow(next_window, renderer),
      _score(score) {
  // clang-format on

  _dispatcher = std::make_shared<Dispatcher>(options);
  _widget_score = std::make_unique<WidgetScore>(WidgetScoreType::Top, screen_size, score, renderer);

  // Geometry
  const kebb::point target_center_aera(
      {static_cast<uint16_t>(screen_size.w / 2), static_cast<uint16_t>(screen_size.h / 2)});
  const uint16_t target_radius_aera(int16_t(screen_size.w * 0.4));

  // Limit the amount of threads if needed
  uint16_t nb_targets = std::stoi(options->get(OptionName::Targets));
  if (nb_targets >= _dispatcher->number_of_chars())
    nb_targets = _dispatcher->number_of_chars() - 3; // Remove 3 to create a difficulty

  for (uint8_t i = 0; i < nb_targets; ++i)
    _targets.emplace_back(Target(target_center_aera, target_radius_aera,
                                 _renderer->font_char_size(FontName::F_Target),
                                 std::stoi(options->get(OptionName::Speed)), _dispatcher, _score));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, &t));

  _countdown_value = std::stoi(options->get(OptionName::Countdown));
  _score->reset();
  _score->start_timer();
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
// RENDER ---------------------------------------------------------------------------------------------
void WindowGame::render() {

  // Up timer
  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    control_escape();
  }

  _renderer->clear_screen();
  _widget_score->render(time_seconds);

  for (auto &target : _targets)
    target.render(_renderer->renderer(), _renderer->font(FontName::F_Target));

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

    if (target.check_keycode(keycode))
      return;
  }

  _score->up_fail();
}
