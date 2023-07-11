#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "widget/widget_base.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Renderer {
public:
  Renderer(boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target, uint16_t font_size_score);
  ~Renderer();

  void UpdateWindowTitle(uint16_t fps); // TODO: Up title

  TTF_Font *font_target();
  TTF_Font *font_score();
  boxsize char_size_target() const;
  boxsize char_size_score() const;

  SDL_Renderer *renderer();

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  TTF_Font *_font_target;
  TTF_Font *_font_score;

  boxsize _char_size_target;
  boxsize _char_size_score;

  const boxsize _screen_size;
  const uint16_t _scale_factor;
};

#endif
