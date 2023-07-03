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

  // std::vector<SDL_Texture *> image_targets;
  SDL_Texture *new_image;

  void render_target(Target &target);
  void render_targets(std::vector<Target *> targets);
  std::vector<SDL_Texture *> _images;
  // Target test_target;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
