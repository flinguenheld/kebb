#include "controller.h"
#include "game.h"
#include "option/option_file.h"
#include "renderer.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

  auto options = std::make_shared<OptionFile>();
  options->read();

  std::cout << "Resolution: " << options->get(OptionName::Resolution) << std::endl;
  boxsize screen_size;
  uint16_t scale_factor;
  switch (std::stoi(options->get(OptionName::Resolution))) {
  case 480:
    screen_size = {480, 480};
    scale_factor = 20; // FIX: Adjust factor ?, otherwise, remove switch
    break;
  case 640:
    screen_size = {640, 640};
    scale_factor = 10;
    break;
  case 800:
    screen_size = {800, 800};
    scale_factor = 10;
    break;
  default:
    screen_size = {1024, 1024};
    scale_factor = 5;
    break;
  }

  // --
  const uint16_t target_font_size = uint16_t(screen_size.w * scale_factor * 0.072);
  const uint16_t score_font_size = uint16_t(screen_size.w * scale_factor * 0.04);
  const uint16_t menu_font_size = uint16_t(screen_size.w * scale_factor * 0.05);

  // NOTE: Manage colours here ?

  auto renderer = std::make_shared<Renderer>(screen_size, scale_factor, target_font_size, score_font_size,
                                             menu_font_size);
  auto score = std::make_shared<Score>();

  Controller controller;
  Game game(screen_size.scale(scale_factor), score, renderer, options);
  game.Run(controller, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  return 0;
}
