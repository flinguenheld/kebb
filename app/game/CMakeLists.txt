set(EXE_SOURCES ${EXE_SOURCES}
    game/dispatcher.cpp
    game/score.cpp
    game/target.cpp

    game/window/window_game.cpp
    game/window/window_gameover.cpp
    game/window/widget_score.cpp

    game/window/survival_mode/widget_gauge.cpp
    game/window/survival_mode/window_survival_mode.cpp
    game/window/survival_mode/window_welcome_survival.cpp

    game/window/timer_mode/window_timer_mode.cpp
    game/window/timer_mode/window_welcome_timer.cpp

    PARENT_SCOPE)

