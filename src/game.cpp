#include "game.h"
#include "SDL.h"
#include "SDL_timer.h"
#include <exception>
#include <iostream>
#include <memory>
#include <string>

Game::Game(std::size_t grid_width, std::size_t grid_height, int center_target_x, int center_target_y,
           int radius_target)
    : snake(grid_width, grid_height), engine(dev()), random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)), random_plus(0, 359),
      _dispatcher(std::make_shared<Dispatcher>()) {

  // FIX:: Remove from constructor to take directly the Font ptr
  for (int i = 0; i < 20; ++i)
    _targets.emplace_back(Target(center_target_x, center_target_y, radius_target, _dispatcher));

  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  // for (int i = 0; i < 2; ++i)
  //   _targets.emplace_back(Target(600, 300, 300, _dispatcher));

  std::vector<std::thread> threads;

  for (auto &t : _targets) {
    t.setFont(renderer.font());
    threads.emplace_back(std::thread(&Target::update, &t));
  }

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, _targets);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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

  for (auto &t : _targets) {
    t.stop();
  }
  for (auto &t : threads) {
    t.join();
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {

  // NOTE: Normaly useless with threads !
  // for (auto &t : _targets) {
  //   t.update();
  // }

  if (!snake.alive)
    return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
