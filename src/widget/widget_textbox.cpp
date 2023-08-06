#include "widget_textbox.h"
#include "utils.h"

WidgetTextBox::WidgetTextBox(kebb::point position, kebb::boxsize size)
    : WidgetBase(position, size), _text("") {
  _color_text = kebb::color(kebb::ColorName::C_Text);
}
WidgetTextBox::~WidgetTextBox() {}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
void WidgetTextBox::set_text(std::string &&text) { _text = std::move(text); }
std::string WidgetTextBox::get_text() const { return _text; }
void WidgetTextBox::set_color_text(SDL_Color &&color) { _color_text = std::move(color); }

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WidgetTextBox::render(SDL_Renderer *renderer, TTF_Font *font) const {

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
