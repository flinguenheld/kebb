#include "window_game_timer.h"

// clang-format off
WindowGameTimer::WindowGameTimer(kebb::boxsize screen_size,
                       std::shared_ptr<kebb::WindowName> next_window,
                       std::shared_ptr<Renderer> renderer,
                       std::shared_ptr<Score> score,
                       std::shared_ptr<OptionFile> options)
    : WindowGame(screen_size, next_window, renderer, score, options)
// clang-format on
{}

WindowGameTimer::~WindowGameTimer() {}
