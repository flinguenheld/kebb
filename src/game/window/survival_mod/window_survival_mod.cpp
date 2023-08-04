#include "window_survival_mod.h"

// clang-format off
WindowSurvivalMod::WindowSurvivalMod(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options),
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
  switch (stoi(_options->get(OptionName::SurvivalDifficulty))) {
  case 0: // Very easy
    _price_fail = 1;
    _price_miss = 1;

    _max_fail = 50;
    _max_miss = 50;

    _levels = {{32, 3, 20},  {32, 4, 40},  {30, 4, 60},  {30, 5, 80},
               {28, 5, 100}, {28, 6, 120}, {26, 6, 140}, {26, 7, 160}};
    break;

  case 1: // Easy   // TODO: Adapt the difficulty
    _price_fail = 1;
    _price_miss = 1;

    _max_fail = 30;
    _max_miss = 20;

    _levels = {{30, 4, 20},  {30, 5, 40},  {28, 5, 60},  {28, 6, 80},
               {26, 6, 100}, {26, 7, 120}, {24, 7, 140}, {24, 8, 160}};
    break;
  case 2: // Normal
    _price_fail = 2;
    _price_miss = 1;

    _max_fail = 20;
    _max_miss = 30;

    _levels = {{25, 4, 20},  {25, 5, 40},  {20, 5, 60},  {20, 6, 80},
               {18, 6, 100}, {18, 7, 120}, {18, 7, 140}, {18, 8, 160}};
    break;
  case 3: // Hard
    _price_fail = 3;
    _price_miss = 2;

    _max_fail = 20;
    _max_miss = 30;

    _levels = {{30, 4, 20},  {30, 5, 40},  {28, 5, 60},  {28, 6, 80},
               {26, 6, 100}, {26, 7, 120}, {24, 7, 140}, {24, 8, 160}};
    break;
  case 4: // Very hard
    _price_fail = 4;
    _price_miss = 3;

    _max_fail = 20;
    _max_miss = 30;

    _levels = {{30, 4, 20},  {30, 5, 40},  {28, 5, 60},  {28, 6, 80},
               {26, 6, 100}, {26, 7, 120}, {24, 7, 140}, {24, 8, 160}};
    break;
  case 5: // Impossible
    _price_fail = 5;
    _price_miss = 4;

    _max_fail = 5;
    _max_miss = 10;

    _levels = {{30, 4, 20},  {30, 5, 40},  {28, 5, 60},  {28, 6, 80},
               {26, 6, 100}, {26, 7, 120}, {24, 7, 140}, {24, 8, 160}};
    break;
  }

  // First level --
  // Threads
  for (uint8_t i = 0; i < _levels[0].nb_target; ++i)
    _targets.emplace_back(std::make_shared<Target>(_target_center_aera, _target_radius_aera,
                                                   _renderer->font_char_size(FontName::F_Target),
                                                   _levels[0].waiting_time, _dispatcher, _score));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, t));

  _score->reset();
  _score->start_timer();
}

WindowSurvivalMod::~WindowSurvivalMod() {}

// ----------------------------------------------------------------------------------------------------
// TARGETS --------------------------------------------------------------------------------------------
void WindowSurvivalMod::add_target(uint16_t waiting_time) {

  if (_targets.size() < _nb_max_target) {

    auto new_target = std::make_shared<Target>(Target(_target_center_aera, _target_radius_aera,
                                                      _renderer->font_char_size(FontName::F_Target),
                                                      waiting_time, _dispatcher, _score));

    _threads.emplace_back(std::thread(&Target::update, new_target));
    _targets.emplace_back(new_target);
  }
}

void WindowSurvivalMod::remove_target() {

  if (_targets.size() > 0) {
    _targets.back()->stop();
    _threads.back().join();

    _targets.pop_back();
    _threads.pop_back();
  }
}

// ----------------------------------------------------------------------------------------------------
// POINTS ---------------------------------------------------------------------------------------------
void WindowSurvivalMod::up_points() {

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
void WindowSurvivalMod::logic() {

  if (_score->miss() >= _max_miss)
    control_escape(); // TODO: Add a cool window with an abstract
  if (_score->fail() >= _max_fail)
    control_escape(); // TODO: Add a cool window with an abstract

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
  _widget_gauge->set_text(std::to_string(it - _levels.begin() + 1));

  // Last level !
  if (it == _levels.end() - 1) {

    if (percentage >= 100) {
      std::cout << "c'est gagné !!!!" << std::endl;
      control_escape(); // TODO: Add a cool window with an abstract
    }
  } else {

    // Number of targets
    while (_targets.size() < (*it).nb_target && _targets.size() < _nb_max_target)
      add_target((*it).waiting_time);
    while (_targets.size() > (*it).nb_target && _targets.size() > 0)
      remove_target();

    // Speed
    for (auto &t : _targets)
      t->set_waiting_time((*it).waiting_time);
  }

  // Up time
  _widget_score->logic(_score->seconds_spent());
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowSurvivalMod::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  _widget_gauge->render();
  WindowGame::render();
}
