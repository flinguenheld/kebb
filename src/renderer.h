#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "snake.h"
#include "target.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class Renderer {
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t grid_width,
           const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, Target &test_target);
  void UpdateWindowTitle(int score, int fps);

  TTF_Font *font();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  TTF_Font *_font;

  SDL_Texture *image;

  // Target test_target;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
