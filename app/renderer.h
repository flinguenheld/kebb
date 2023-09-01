#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"
#include "SDL_pixels.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include "config.h"
#include "utils.h"
#include <iostream>
#include <memory>
#include <vector>

enum class FontName {
  F_Target,
  F_Game,
  F_Menu,
};

class Renderer {
public:
  Renderer(widget::boxsize screen_size, uint16_t scale_factor, uint16_t font_size_target,
           uint16_t font_size_game, uint16_t font_size_menu);
  ~Renderer();

  bool init_ok() const;
  SDL_Renderer *renderer();

  void update_window_title(uint16_t fps);
  void clear_screen();

  TTF_Font *font(FontName fn);
  widget::boxsize font_char_size(FontName fn) const;

private:
  SDL_Window *_window;
  SDL_Renderer *_renderer;

  TTF_Font *_font_target;
  TTF_Font *_font_game;
  TTF_Font *_font_menu;

  widget::boxsize _char_size_target;
  widget::boxsize _char_size_game;
  widget::boxsize _char_size_menu;

  const widget::boxsize _screen_size;
  const uint16_t _scale_factor;
  SDL_Color _color_background;

  bool _init_ok;
};

#endif
