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

  // TODO: Remove that, but the renderer needs the font size
  const point target_center_aera = {screen_size.w * scale_factor / 2, screen_size.h * scale_factor / 2};
  constexpr uint16_t target_radius_aera = uint16_t(screen_size.w * scale_factor * 0.4);
  constexpr uint16_t target_font_size = uint16_t(target_radius_aera * 0.18);
  constexpr boxsize target_char_size = {static_cast<uint16_t>(target_font_size * 0.6),
                                        static_cast<uint16_t>(target_font_size * 1.15)};

  constexpr uint16_t score_font_size = uint16_t(target_radius_aera * 0.08);
  constexpr boxsize score_char_size = {static_cast<uint16_t>(score_font_size * 0.6),
                                       static_cast<uint16_t>(score_font_size * 1.15)};

  auto score = std::make_shared<Score>(screen_size.w * scale_factor, score_char_size);
  auto renderer =
      std::make_shared<Renderer>(screen_size, scale_factor, target_font_size, score_font_size, score);

  Controller controller;
  Game game(screen_size, scale_factor, score, renderer);
  game.Run(controller, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  return 0;
}
