#include "game.h"

Game::Game(point target_center_aera, uint16_t target_radius_aera, boxsize target_char_size,
           std::shared_ptr<Score> score)
    : _score(score) {
  _dispatcher = std::make_shared<Dispatcher>();

  for (uint8_t i = 0; i < 5; ++i)
    _targets.emplace_back(
        Target(target_center_aera, target_radius_aera, target_char_size, _dispatcher, _score));
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // Start threads
  std::vector<std::thread> threads;
  for (auto &t : _targets) {
    threads.emplace_back(std::thread(&Target::update, &t));
  }

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, _targets);
    renderer.Render(_targets);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    // if (frame_duration < target_frame_duration) {
    //   SDL_Delay(target_frame_duration - frame_duration);
    // }
    SDL_Delay(5);
  }

  for (auto &t : _targets) {
    t.stop();
  }
  for (auto &t : threads) {
    t.join();
  }
}
