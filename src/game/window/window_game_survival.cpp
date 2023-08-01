#include "window_game_survival.h"
#include <memory>

// clang-format off
WindowGameSurvival::WindowGameSurvival(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options), _next_level(1)
// clang-format on
{

  // TODO: Adapt to increase the difficuly according to options
  // Limit the amount of threads if needed
  _nb_max_target = _dispatcher->number_of_chars() * 0.6; // Prevent the same amount of target/thread

  for (uint8_t i = 0; i < 3; ++i)
    _targets.emplace_back(std::make_shared<Target>(
        _target_center_aera, _target_radius_aera, _renderer->font_char_size(FontName::F_Target),
        std::stoi(options->get(OptionName::Speed)), _dispatcher, _score));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, t));

  _countdown_value = std::stoi(options->get(OptionName::Countdown));
  _score->reset();
  _score->start_timer();
}

WindowGameSurvival::~WindowGameSurvival() {}

void WindowGameSurvival::add_target() {

  if (_targets.size() < _nb_max_target) {

    auto new_target = std::make_shared<Target>(Target(_target_center_aera, _target_radius_aera,
                                                      _renderer->font_char_size(FontName::F_Target), 10,
                                                      _dispatcher, _score));

    _threads.emplace_back(std::thread(&Target::update, new_target));
    _targets.push_back(new_target);
  }
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowGameSurvival::logic() {

  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    control_escape();
  }

  if (_score->success() == _next_level) {
    add_target();
    _next_level += 1;
  }

  _widget_score->logic(time_seconds);

  // TODO: Check scores to leave if there are too many fails/misses
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowGameSurvival::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  WindowGame::render();
}
