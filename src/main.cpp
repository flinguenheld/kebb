#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <iostream>

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // FIX: More elegant ? and set the font size !!
  constexpr int TARGET_CENTER_X{kScreenWidth * 3 / 2};
  constexpr int TARGET_CENTER_Y{kScreenHeight * 3 / 2};
  constexpr int TARGET_RADIUS{int(kScreenWidth * 3 * 0.7)};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);

  // SDL_RenderSetLogicalSize(renderer, , 15);

  Controller controller;
  Game game(kGridWidth, kGridHeight, TARGET_CENTER_X, TARGET_CENTER_Y, TARGET_RADIUS);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}
