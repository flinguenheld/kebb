#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "utils.h"
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
  Renderer(kebb::boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
           uint16_t font_size_score, uint16_t font_size_menu);
  ~Renderer();

  void update_window_title(uint16_t fps);
  void clear_screen();

  SDL_Renderer *renderer();

  TTF_Font *font(FontName fn);
  kebb::boxsize font_char_size(FontName fn) const;

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  TTF_Font *_font_target;
  TTF_Font *_font_score;
  TTF_Font *_font_menu;

  kebb::boxsize _char_size_target;
  kebb::boxsize _char_size_score;
  kebb::boxsize _char_size_menu;

  const kebb::boxsize _screen_size;
  const uint16_t _scale_factor;
  SDL_Color _color_background;
};

#endif
