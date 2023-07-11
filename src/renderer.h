#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "utils.h"
#include "widget/widget_base.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum class FontName {
  F_Target,
  F_Score,
  F_Menu,
};

class Renderer {
public:
  Renderer(boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target, uint16_t font_size_score,
           uint16_t font_size_menu);
  ~Renderer();

  void UpdateWindowTitle(uint16_t fps); // TODO: Up title

  SDL_Renderer *renderer();

  TTF_Font *font(FontName fn);
  boxsize font_char_size(FontName fn) const;

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  TTF_Font *_font_target;
  TTF_Font *_font_score;
  TTF_Font *_font_menu;

  boxsize _char_size_target;
  boxsize _char_size_score;
  boxsize _char_size_menu;

  const boxsize _screen_size;
  const uint16_t _scale_factor;
};

#endif
