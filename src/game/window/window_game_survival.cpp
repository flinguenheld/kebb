#include "window_game_survival.h"
#include <cstdint>
#include <iostream>
#include <memory>

// clang-format off
WindowGameSurvival::WindowGameSurvival(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options)
// clang-format on
{

  // TODO: Adapt to increase the difficuly according to difficulty !!!

  switch (stoi(_options->get(OptionName::SurvivalDifficulty))) {
  case 0:
    std::cout << "Mode very easy" << std::endl;
    // FIX: Create a struct with the current speed // nb of threads // success to reach
    _levels = {{20, 3, 5},  {18, 3, 10}, {18, 4, 15}, {16, 4, 20},
               {16, 5, 25}, {14, 5, 30}, {14, 6, 35}, {12, 6, 40}};
    break;
  case 1:
    break;
  case 2:
    break;
  case 3:
    break;
  case 4:
    break;
  case 5:
    break;
  }

  _current_level = _levels.begin();

  // Threads --
  _nb_max_target = _dispatcher->number_of_chars() * 0.6; // Prevent the same targets/thread amount.

  for (uint8_t i = 0; i < (*_current_level).nb_target; ++i)
    _targets.emplace_back(std::make_shared<Target>(_target_center_aera, _target_radius_aera,
                                                   _renderer->font_char_size(FontName::F_Target),
                                                   (*_current_level).waiting_time, _dispatcher, _score));

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
                                                      _renderer->font_char_size(FontName::F_Target),
                                                      (*_current_level).waiting_time, _dispatcher, _score));

    _threads.emplace_back(std::thread(&Target::update, new_target));
    _targets.emplace_back(new_target);
  }
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowGameSurvival::logic() {

  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    control_escape();
  }

  if (_current_level != _levels.end() && (*_current_level).next_level == _score->success()) {

    _current_level++;
    if (_current_level == _levels.end())
      return;

    std::cout << "Next level !" << std::endl;

    while (_targets.size() < (*_current_level).nb_target)
      add_target();

    for (auto &t : _targets)
      t->set_waiting_time((*_current_level).waiting_time);
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
