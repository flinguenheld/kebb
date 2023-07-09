#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "score.h"
#include "snake.h"
#include "target.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

class Renderer {
public:
  Renderer(int screen_width, int screen_height, int scale_factor, int font_size, const std::size_t grid_width,
           const std::size_t grid_height, std::shared_ptr<Score> score);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, const std::vector<Target> &targets);
  void UpdateWindowTitle(int score, int fps);

  TTF_Font *font();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;
  TTF_Font *_font;
  TTF_Font *_font_scores;

  const int _screen_width;
  const int _screen_height;
  const int _scale_factor;

  std::shared_ptr<Score> _score;

  // TODO: Remove :
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
