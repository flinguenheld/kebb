#include "window_game_survival.h"
#include <cstdint>
#include <string>
#include <sys/types.h>

// clang-format off
WindowGameSurvival::WindowGameSurvival(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options),
    _previous_level(0),
    _previous_fail(0),
    _previous_miss(0),
    _previous_success(0),
    _points(0)
// clang-format on
{

  // Gauge
  _widget_gauge = std::make_unique<WidgetGauge>(screen_size, renderer);
  _widget_gauge->set_percentage(100);

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

void WindowGameSurvival::up_points() {

  auto miss = _score->miss();
  auto fail = _score->fail();
  auto success = _score->success();

  auto new_miss = (miss > _previous_miss) ? miss - _previous_miss : 0;
  auto new_fail = (fail > _previous_fail) ? fail - _previous_fail : 0;
  auto new_success = (success > _previous_success) ? success - _previous_success : 0;

  _points -= new_miss * 2;
  _points -= new_fail * 3;
  _points += new_success;

  if (_points < 0)
    _points = 0;

  _previous_miss = miss;
  _previous_fail = fail;
  _previous_success = success;
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowGameSurvival::logic() {

  // Find the current level according to the points
  up_points();

  uint16_t previous_level = 0;
  std::vector<Level>::iterator it = _levels.begin();
  for (; it != _levels.end(); ++it) {
    if ((*it).next_level > _points)
      break;

    previous_level = (*it).next_level;
  }

  // TODO: Last level ?

  auto percentage = (_points - previous_level) * 100 / (((*it).next_level) - previous_level);
  _widget_gauge->set_percentage(percentage);
  _widget_gauge->set_text(std::to_string(it - _levels.begin() + 1));

  // Adapt speed & nb of threads

  // Set a normal time
  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  _widget_score->logic(time_seconds);

  // TODO: Check scores to leave if there are too many fails/misses
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowGameSurvival::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  _widget_gauge->render();
  WindowGame::render();
}
