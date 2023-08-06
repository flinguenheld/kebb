#include "window_timer_mod.h"
#include "file/option_file.h"
#include "utils.h"
#include <string>

// clang-format off
WindowTimerMod::WindowTimerMod(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<RecordFile> records,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, records, options)
// clang-format on
{

  // Limit the amount of threads if needed
  uint16_t nb_targets = options->get_uint(OptionName::Targets);
  if (nb_targets >= _dispatcher->number_of_chars())
    nb_targets = _dispatcher->number_of_chars() * 0.6; // Remove to create a difficulty

  for (uint8_t i = 0; i < nb_targets; ++i)
    _targets.emplace_back(std::make_shared<Target>(
        _target_center_aera, _target_radius_aera, _renderer->font_char_size(FontName::F_Target),
        options->get_uint(OptionName::Speed), _dispatcher, _score));

  // Start !
  for (auto &t : _targets)
    _threads.emplace_back(std::thread(&Target::update, t));

  _countdown_value = options->get_uint(OptionName::Countdown);
  _score->reset();
  _score->start_timer();
}

WindowTimerMod::~WindowTimerMod() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowTimerMod::logic() {

  int16_t time_seconds = _countdown_value - _score->seconds_spent();
  if (time_seconds <= 0) {
    control_escape();
  }

  _widget_score->logic(time_seconds);
}
// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowTimerMod::render() const {

  _renderer->clear_screen();
  _widget_score->render();
  WindowGame::render();
}

// ----------------------------------------------------------------------------------------------------
// RECORDS --------------------------------------------------------------------------------------------
void WindowTimerMod::save_record() const {

  _records->add({.mod = uint16_t(kebb::GameMod::M_Timer),
                 .success = _score->success(),
                 .fail = _score->fail(),
                 .miss = _score->miss(),
                 .time_start = _score->seconds_timer_started(),
                 .time_game = _score->seconds_spent(),
                 .speed = _options->get_uint(OptionName::Speed),
                 .nb_target = _options->get_uint(OptionName::Targets)});
}
