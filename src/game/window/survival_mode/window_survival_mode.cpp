#include "window_survival_mode.h"
#include <iostream>

// clang-format off
WindowSurvivalMode::WindowSurvivalMode(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<RecordFile> records,
                       std::shared_ptr<OptionFile> options,
                       std::shared_ptr<LayoutFile> layouts)
    : WindowGame(screen_size, next_window, renderer, records, options, layouts),
    _previous_fail(0),
    _previous_miss(0),
    _previous_success(0),
    _points(0)
// clang-format on
{
  // Gauge
  _widget_gauge = std::make_unique<WidgetGauge>(screen_size, renderer);
  _widget_gauge->set_percentage(100);

  // Levels --
  uint16_t nb_targets = _options->get().survival_nb_targets;
  uint16_t speed = _options->get().survival_speed;
  uint16_t next_level = 0;

  _price_fail = ((speed + nb_targets) / 3 < 1) ? 1 : (speed + nb_targets) / 3;
  _price_miss = ((speed + nb_targets) / 8 < 1) ? 1 : (speed + nb_targets) / 8;

  _max_fail = 10;
  _max_miss = 20;

#ifdef DEBUG
  std::cout << "--------------------------------------------------\n";
  std::cout << "- Start with " << nb_targets << " targets - "
            << " Speed: " << speed << std::endl;

  std::cout << "- price fail: " << _price_fail << std::endl;
  std::cout << "- price miss: " << _price_miss << std::endl;
  std::cout << "- max fail: " << _max_fail << std::endl;
  std::cout << "- max miss: " << _max_miss << std::endl;
#endif

  for (uint16_t i = 0; i < 12; ++i) {
    next_level += (nb_targets + speed) * 4; // NOTE: Add another option ?

    if (i != 0) {
      if (i % 2 == 0)
        ++speed;
      else
        ++nb_targets;
    }

    _levels.push_back({.speed = speed, .nb_target = nb_targets, .points_next_level = next_level});

#ifdef DEBUG
    std::cout << " --- Level " << i << ": speed " << speed << "   nb: " << nb_targets
              << "   next: " << next_level << std::endl;
#endif
  }

  // First level --
  const auto nb_targets_first_level =
      (_nb_max_target < _levels[0].nb_target) ? _nb_max_target : _levels[0].nb_target;

  for (uint8_t i = 0; i < nb_targets_first_level; ++i)
    _targets.emplace_back(std::make_shared<Target>(_target_center_aera, _target_radius_aera,
                                                   _renderer->font_char_size(FontName::F_Target),
                                                   _levels[0].speed, _dispatcher, _score, _layouts));
  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, t));

  _score->reset();
  _score->start_timer();
}

WindowSurvivalMode::~WindowSurvivalMode() {}

// ----------------------------------------------------------------------------------------------------
// TARGETS --------------------------------------------------------------------------------------------
void WindowSurvivalMode::add_target(uint16_t waiting_time) {

  if (_targets.size() < _nb_max_target) {

    auto new_target = std::make_shared<Target>(Target(_target_center_aera, _target_radius_aera,
                                                      _renderer->font_char_size(FontName::F_Target),
                                                      waiting_time, _dispatcher, _score, _layouts));

    _threads.emplace_back(std::thread(&Target::update, new_target));
    _targets.emplace_back(new_target);
  }
}

void WindowSurvivalMode::remove_target() {

  if (_targets.size() > 0) {
    _targets.back()->stop();
    _threads.back().join();

    _targets.pop_back();
    _threads.pop_back();
  }
}

// ----------------------------------------------------------------------------------------------------
// POINTS ---------------------------------------------------------------------------------------------
void WindowSurvivalMode::up_points() {

  auto miss = _score->miss();
  auto fail = _score->fail();
  auto success = _score->success();

  auto new_miss = (miss > _previous_miss) ? miss - _previous_miss : 0;
  auto new_fail = (fail > _previous_fail) ? fail - _previous_fail : 0;
  auto new_success = (success > _previous_success) ? success - _previous_success : 0;

  _points -= new_miss * _price_miss;
  _points -= new_fail * _price_fail;
  _points += new_success;

  if (_points < 0)
    _points = 0;

  _previous_miss = miss;
  _previous_fail = fail;
  _previous_success = success;
}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowSurvivalMode::logic() {

  if (_score->miss() >= _max_miss) {
    _game_status = kebb::GameStatus::S_Loose;
    control_escape();
  }
  if (_score->fail() >= _max_fail) {
    _game_status = kebb::GameStatus::S_Loose;
    control_escape();
  }

  // Find the current level according to the points
  up_points();

  // --
  uint16_t previous_level = 0;
  std::vector<Level>::iterator it = _levels.begin();
  for (; it != _levels.end(); ++it) {
    if ((*it).points_next_level > _points || it == _levels.end() - 1)
      break;

    previous_level = (*it).points_next_level;
  }

  auto percentage = (_points - previous_level) * 100 / (((*it).points_next_level) - previous_level);
  _widget_gauge->set_percentage(percentage);
  _widget_gauge->set_level(it - _levels.begin() + 1);

  // Last level !
  if (it == _levels.end() - 1) {

    if (percentage >= 100) {
      _game_status = kebb::GameStatus::S_Win;
      control_escape();
    }
  } else {

    // Number of targets
    while (_targets.size() < (*it).nb_target && _targets.size() < _nb_max_target)
      add_target((*it).speed);
    while (_targets.size() > (*it).nb_target && _targets.size() > 0)
      remove_target();

    // Speed
    for (auto &t : _targets)
      t->set_speed((*it).speed);
  }

  // Up time
  _widget_score->logic(_score->seconds_spent());
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowSurvivalMode::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  _widget_gauge->render();
  WindowGame::render();
}

// ----------------------------------------------------------------------------------------------------
// RECORDS --------------------------------------------------------------------------------------------
void WindowSurvivalMode::save_record() const {

  _records->add({.mode = uint16_t(kebb::GameMode::M_Survival),
                 .status = uint16_t(_game_status),
                 .success = _score->success(),
                 .fail = _score->fail(),
                 .miss = _score->miss(),
                 .time_start = _score->seconds_timer_started(),
                 .time_game = _score->seconds_spent(),
                 .survival_nb_targets = _options->get().survival_nb_targets,
                 .survival_speed = _options->get().survival_speed,
                 .survival_level = _widget_gauge->get_level()});
}
