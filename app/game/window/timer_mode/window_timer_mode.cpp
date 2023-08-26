#include "window_timer_mode.h"

// clang-format off
WindowTimerMode::WindowTimerMode(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<RecordFile> records,
                       std::shared_ptr<OptionFile> options,
                       std::shared_ptr<LayoutFile> layouts)
    : WindowGame(screen_size, next_window, renderer, records, options, layouts)
// clang-format on
{

  // Limit the amount of threads if needed
  const auto nb_targets =
      (_nb_max_target < options->get().timer_nb_targets) ? _nb_max_target : options->get().timer_nb_targets;

  for (uint8_t i = 0; i < nb_targets; ++i)
    _targets.emplace_back(std::make_shared<Target>(
        _target_center_aera, _target_radius_aera, _renderer->font_char_size(FontName::F_Target),
        options->get().timer_speed, _dispatcher, _score, _layouts));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, t));

  _countdown_value = options->get().timer_countdown;
  _score->reset();
  _score->start_timer();
}

WindowTimerMode::~WindowTimerMode() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowTimerMode::logic() {

  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    _game_status = kebb::GameStatus::S_TimeUp;
    control_escape();
  }

  _widget_score->logic(time_seconds);
}
// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowTimerMode::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  WindowGame::render();
}

// ----------------------------------------------------------------------------------------------------
// RECORDS --------------------------------------------------------------------------------------------
void WindowTimerMode::save_record() const {

  _records->add({.mode = uint16_t(kebb::GameMode::M_Timer),
                 .status = uint16_t(_game_status),
                 .success = _score->success(),
                 .fail = _score->fail(),
                 .miss = _score->miss(),
                 .time_start = _score->seconds_timer_started(),
                 .time_game = _score->seconds_spent(),
                 .timer_speed = _options->get().timer_speed,
                 .timer_nb_target = _options->get().timer_nb_targets});
}
