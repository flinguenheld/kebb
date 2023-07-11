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

  constexpr boxsize screen_size = {640, 640};
  constexpr uint16_t scale_factor = 10;

  constexpr uint16_t target_font_size = uint16_t(screen_size.w * scale_factor * 0.072);
  constexpr uint16_t score_font_size = uint16_t(screen_size.w * scale_factor * 0.04);

  auto renderer = std::make_shared<Renderer>(screen_size, scale_factor, target_font_size, score_font_size);
  auto score = std::make_shared<Score>(screen_size.w * scale_factor, renderer);

  Controller controller;
  Game game(screen_size, scale_factor, score, renderer);
  game.Run(controller, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  return 0;
}
