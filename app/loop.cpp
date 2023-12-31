#include "loop.h"
#include <cstdint>

// clang-format off
Loop::Loop(widget::boxsize screen_size, std::shared_ptr<Renderer> renderer,
           std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts) :
      _screen_size(screen_size),
      _renderer(renderer),
      _options(options),
      _layouts(layouts)
{
  _records = std::make_shared<RecordFile>();
}
// clang-format on

void Loop::run(Controller &controller) {
  uint32_t title_timestamp = SDL_GetTicks();
  uint32_t frame_end;
  uint32_t frame_count = 0;
  bool running = true;

  auto next_window_id = std::make_shared<uint8_t>(uint8_t(kebb::WindowName::W_None));
  _current_window = std::make_shared<WindowWelcome>(_screen_size, next_window_id, _renderer, _options);

  // Main game loop.
  while (running) {

    controller.handle_input(running, _current_window);
    _current_window->logic();
    _current_window->render();

    // Window management
    if (*next_window_id != uint8_t(kebb::WindowName::W_None)) {

      _current_window.reset(); // NOTE: Mandatory/usefull or not ?

      switch (*next_window_id) {
      case uint8_t(kebb::WindowName::W_About):
        _current_window = std::make_shared<WindowAbout>(_screen_size, next_window_id, _renderer);
        break;
      case uint8_t(kebb::WindowName::W_GameOver):
        _current_window =
            std::make_shared<WindowGameOver>(_screen_size, next_window_id, _renderer, _records, _options);
        break;
      case uint8_t(kebb::WindowName::W_GameSurvival):
        _current_window = std::make_shared<WindowSurvivalMode>(_screen_size, next_window_id, _renderer,
                                                               _records, _options, _layouts);
        break;
      case uint8_t(kebb::WindowName::W_GameTimer):
        _current_window = std::make_shared<WindowTimerMode>(_screen_size, next_window_id, _renderer, _records,
                                                            _options, _layouts);
        break;
      case uint8_t(kebb::WindowName::W_Option):
        _current_window =
            std::make_shared<WindowOption>(_screen_size, next_window_id, _renderer, _options, _layouts);
        break;
      case uint8_t(kebb::WindowName::W_Record):
        _current_window = std::make_shared<WindowRecord>(_screen_size, next_window_id, _renderer, _records);
        break;
      case uint8_t(kebb::WindowName::W_Welcome):
        _current_window = std::make_shared<WindowWelcome>(_screen_size, next_window_id, _renderer, _options);
        break;
      case uint8_t(kebb::WindowName::W_WelcomeSurvival):
        _current_window =
            std::make_shared<WindowWelcomeSurvival>(_screen_size, next_window_id, _renderer, _options);
        break;
      case uint8_t(kebb::WindowName::W_WelcomeTimer):
        _current_window =
            std::make_shared<WindowWelcomeTimer>(_screen_size, next_window_id, _renderer, _options);
        break;
      default: // W_Ouit
        running = false;
        break;
      }

      *next_window_id = uint8_t(kebb::WindowName::W_None);
    }

    frame_end = SDL_GetTicks();
    frame_count++;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->update_window_title(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    SDL_Delay(5); // NOTE: Is 5 ok ?
  }
}
