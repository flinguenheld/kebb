#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <iostream>
#include <memory>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  constexpr uint16_t screen_width = 640;
  constexpr uint16_t screen_height = 640;
  constexpr uint16_t scale_factor = 10;

  constexpr uint16_t target_center_x = screen_width * scale_factor / 2;
  constexpr uint16_t target_center_y = screen_height * scale_factor / 2;
  constexpr uint16_t target_radius = uint16_t(screen_width * scale_factor * 0.4);

  constexpr uint16_t font_size = uint16_t(target_radius * 0.15);

  // TODO: Use a boxsize to set the target char size
  constexpr uint16_t font_size_score = uint16_t(target_radius * 0.08);
  constexpr boxsize char_size_score = {static_cast<uint16_t>(font_size_score * 0.6),
                                       static_cast<uint16_t>(font_size_score * 1.15)};

  std::shared_ptr<Score> score = std::make_shared<Score>(screen_width * scale_factor, char_size_score);

  Renderer renderer(screen_width, screen_height, scale_factor, font_size, kGridWidth, kGridHeight, score);

  Controller controller(score);
  Game game(kGridWidth, kGridHeight, target_center_x, target_center_y, target_radius, font_size, score);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
