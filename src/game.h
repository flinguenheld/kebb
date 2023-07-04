#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "target.h"
#include <cstddef>
#include <random>
#include <thread>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height, int center_target_x, int center_target_y,
       int radius_target);
  void Run(Controller const &controller, Renderer &renderer, std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake;
  SDL_Point food;

  std::vector<Target> _targets;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_plus;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif
