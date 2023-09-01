#include "widget_textbox.h"

WidgetTextBox::WidgetTextBox(widget::point position, widget::boxsize char_size, TextBoxAlign alignment)
    : WidgetBase(position, char_size), _text(""), _char_size(char_size), _alignment(alignment) {
  _color_text = widget::color(widget::ColorName::C_Text);
}

WidgetTextBox::WidgetTextBox(widget::point position, widget::boxsize char_size, TextBoxAlign alignment,
                             std::string &&text, SDL_Color &&color_text)
    : WidgetBase(position, char_size), _text(""), _char_size(char_size), _alignment(alignment) {
  move_text(std::move(text));
  set_color_text(std::move(color_text));
}

WidgetTextBox::~WidgetTextBox() {}

// ----------------------------------------------------------------------------------------------------
// ACCESSORS ------------------------------------------------------------------------------------------
void WidgetTextBox::move_text(std::string &&text) {
  _text = std::move(text);
  _size.w = _char_size.w * _text.length();
  _size.h = _char_size.h;
}
void WidgetTextBox::set_text(std::string txt) { move_text(std::move(txt)); }

std::string WidgetTextBox::get_text() const { return _text; }
void WidgetTextBox::set_color_text(SDL_Color &&color) { _color_text = std::move(color); }

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WidgetTextBox::render(SDL_Renderer *renderer, TTF_Font *font) const {

  if (_visible && !_text.empty()) {

    SDL_Surface *new_textSurface = TTF_RenderUTF8_Shaded(font, _text.c_str(), _color_text, _color);

    if (new_textSurface == NULL) {
      printf("Unable to render text surface! SDL_ttf Error: %s with the value: %s\n", TTF_GetError(),
             _text.c_str());
    } else {

      auto new_texture = SDL_CreateTextureFromSurface(renderer, new_textSurface);
      if (new_texture == NULL)
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
      else {

        SDL_Rect renderQuad;
        if (_alignment == TextBoxAlign::TB_Center)
          renderQuad = {_position.x - _size.w / 2, _position.y - _size.h / 2, _size.w, _size.h};
        else
          renderQuad = {_position.x, _position.y, _size.w, _size.h};

        SDL_Point center = {};
        SDL_RendererFlip flip = {};

        SDL_RenderCopyEx(renderer, new_texture, nullptr, &renderQuad, 0, &center, flip);

        // Get rid of elements
        SDL_DestroyTexture(new_texture);
      }

      SDL_FreeSurface(new_textSurface);
    }
  }
}
