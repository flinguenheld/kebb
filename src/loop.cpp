#include "loop.h"
#include "game/window/window_game_timer.h"
#include "welcome/window_welcome_survival.h"

// clang-format off
Loop::Loop(kebb::boxsize screen_size, std::shared_ptr<Score> score,
           std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options) :
      _screen_size(screen_size),
      _score(score),
      _renderer(renderer),
      _options(options)
{
  _dispatcher = std::make_shared<Dispatcher>(_options);
}
// clang-format on

void Loop::run(Controller &controller) {
  uint32_t title_timestamp = SDL_GetTicks();
  uint32_t frame_end;
  uint32_t frame_count = 0;
  bool running = true;

  auto next_window_name = std::make_shared<kebb::WindowName>(kebb::WindowName::W_None);
  _current_window = std::make_shared<WindowWelcome>(_screen_size, next_window_name, _renderer);

  // Main game loop.
  while (running) {

    controller.handle_input(running, _current_window);
    _current_window->render();

    // Window management
    if (*next_window_name != kebb::WindowName::W_None) {

      _current_window.reset(); // NOTE: Mandatory/usefull or not ?

      switch (*next_window_name) {
      case kebb::WindowName::W_GameTimer:
        _current_window =
            std::make_shared<WindowGameTimer>(_screen_size, next_window_name, _renderer, _score, _options);
        break;
      case kebb::WindowName::W_GameSurvival:
        _current_window =
            std::make_shared<WindowGameSurvival>(_screen_size, next_window_name, _renderer, _score, _options);
        break;
      case kebb::WindowName::W_Pause:
        _current_window = std::make_shared<WindowPause>(_screen_size, next_window_name, _renderer, _score);
        break;
      case kebb::WindowName::W_Welcome:
        _current_window = std::make_shared<WindowWelcome>(_screen_size, next_window_name, _renderer);
        break;
      case kebb::WindowName::W_WelcomeSurvival:
        _current_window =
            std::make_shared<WindowWelcomeSurvival>(_screen_size, next_window_name, _renderer, _options);
        break;
      case kebb::WindowName::W_WelcomeTimer:
        _current_window =
            std::make_shared<WindowWelcomeTimer>(_screen_size, next_window_name, _renderer, _options);
        break;
      case kebb::WindowName::W_Option:
        _current_window = std::make_shared<WindowOption>(_screen_size, next_window_name, _renderer, _options);
        break;
      case kebb::WindowName::W_About:
        _current_window = std::make_shared<WindowAbout>(_screen_size, next_window_name, _renderer);
        break;
      default: // W_Ouit
        running = false;
        break;
      }

      *next_window_name = kebb::WindowName::W_None;
    }

    frame_end = SDL_GetTicks();
    frame_count++;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->update_window_title(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    SDL_Delay(3); // NOTE: Is 3 ok ?
  }
}
