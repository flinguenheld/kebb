#include "widget_base.h"

WidgetBase::WidgetBase(point position, boxsize size)
    : _position(position), _size(size), _color({255, 255, 255, 1}) {}

point WidgetBase::position() const { return _position; };
boxsize WidgetBase::size() const { return _size; }
SDL_Color WidgetBase::color() const { return _color; }

// ----------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------

WidgetTextBoxBase::WidgetTextBoxBase(point position, boxsize size) : WidgetBase(position, size) {}

void WidgetTextBoxBase::render(SDL_Renderer *renderer, TTF_Font *font) const {

  SDL_Surface *new_textSurface = TTF_RenderUTF8_Shaded(font, _text.c_str(), _color_text, _color);

  if (new_textSurface == NULL)
    printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
  else {

    auto new_texture = SDL_CreateTextureFromSurface(renderer, new_textSurface);
    if (new_texture == NULL)
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    else {

      SDL_Rect renderQuad = {_position.x, _position.y, _size.w, _size.h};
      SDL_Point center = {};
      SDL_RendererFlip flip = {};

      SDL_RenderCopyEx(renderer, new_texture, nullptr, &renderQuad, 0, &center, flip);

      // Get rid of elements
      SDL_DestroyTexture(new_texture);
    }

    SDL_FreeSurface(new_textSurface);
  }
}
