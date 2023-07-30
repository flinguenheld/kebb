#include "window_game_timer.h"

// clang-format off
WindowGameTimer::WindowGameTimer(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options)
// clang-format on
{

  // Limit the amount of threads if needed
  uint16_t nb_targets = std::stoi(options->get(OptionName::Targets));
  if (nb_targets >= _dispatcher->number_of_chars())
    nb_targets = _dispatcher->number_of_chars() * 0.6; // Remove to create a difficulty

  for (uint8_t i = 0; i < nb_targets; ++i)
    _targets.emplace_back(Target(_target_center_aera, _target_radius_aera,
                                 _renderer->font_char_size(FontName::F_Target),
                                 std::stoi(options->get(OptionName::Speed)), _dispatcher, _score));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, &t));

  _countdown_value = std::stoi(options->get(OptionName::Countdown));
  _score->reset();
  _score->start_timer();
}

WindowGameTimer::~WindowGameTimer() {}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowGameTimer::render() {

  _renderer->clear_screen();

  // Up timer
  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    control_escape();
  }

  _widget_score->render(time_seconds);

  WindowGame::render();
}
