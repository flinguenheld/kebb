#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>
#include <memory>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  constexpr int screen_width = 640;
  constexpr int screen_height = 640;
  constexpr int scale_factor = 10;

  constexpr int target_center_x = screen_width * scale_factor / 2;
  constexpr int target_center_y = screen_height * scale_factor / 2;
  constexpr int target_radius = int(screen_width * scale_factor * 0.4);
  constexpr int font_size = int(target_radius * 0.15);

  point p = {1000, 1000};
  std::shared_ptr<Score> score = std::make_shared<Score>(p, 500);

  Renderer renderer(screen_width, screen_height, scale_factor, font_size, kGridWidth, kGridHeight, score);

  Controller controller(score);
  Game game(kGridWidth, kGridHeight, target_center_x, target_center_y, target_radius, font_size, score);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
