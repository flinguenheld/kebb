#include "game.h"

// clang-format off
Game::Game(boxsize screen_size, std::shared_ptr<Score> score,
           std::shared_ptr<Renderer> renderer) :

      _screen_size(screen_size),
      _score(score),
      _renderer(renderer),
      _current_window(nullptr)
{
  _dispatcher = std::make_shared<Dispatcher>();
}

Game::~Game() {
  if (_current_window != nullptr)
    delete _current_window;
}
// clang-format on

void Game::Run(Controller const &controller, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  auto next_window = std::make_shared<WindowName>(WindowName::W_None);
  _current_window = new WindowWelcome(_screen_size, next_window, _renderer);
  // _current_window = new WindowGame(_screen_size, next_window, _renderer, _score);

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _current_window);
    _current_window->render();

    // FIX: Use a unique ptr ?
    if (*next_window != WindowName::W_None) {
      delete _current_window;
      _current_window = nullptr;

      switch (*next_window) {
      case WindowName::W_Game:
        _current_window = new WindowGame(_screen_size, next_window, _renderer, _score);
        break;
      case WindowName::W_Pause:
        _current_window = new WindowPause(_screen_size, next_window, _renderer, _score);
        break;
      case WindowName::W_Welcome:
        _current_window = new WindowWelcome(_screen_size, next_window, _renderer);
        break;
      case WindowName::W_Option:
        _current_window = new WindowOption(_screen_size, next_window, _renderer);
        break;
      default: // W_Ouit
        running = false;
        break;
      }

      *next_window = WindowName::W_None;
    }

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      _renderer->UpdateWindowTitle(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    // if (frame_duration < target_frame_duration) {
    //   SDL_Delay(target_frame_duration - frame_duration);
    // }
    SDL_Delay(10);
  }
}
