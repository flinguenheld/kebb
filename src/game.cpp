#include "game.h"
#include "widget/widget_base.h"

Game::Game(boxsize screen_size, uint16_t scale_factor, std::shared_ptr<Score> score)

    : _score(score), _w_game(screen_size, scale_factor, score) { // TODO: USE general vars
  _dispatcher = std::make_shared<Dispatcher>();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // FIX: Can't be here
  _w_game.start_threads();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, &_w_game);

    _w_game.render(renderer.renderer(), renderer.font(),
                   renderer.font_score()); // FIX: Logic to call the ptr ??

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

  _w_game.stop_threads();
  // for (auto &t : _targets) {
  //   t.stop();
  // }
  // for (auto &t : threads) {
  //   t.join();
  // }
}
