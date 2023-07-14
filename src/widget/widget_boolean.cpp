#include "widget_boolean.h"

WidgetBoolean::WidgetBoolean(point pos_center, boxsize size_char, std::string &&text, bool selected)
    : WidgetSelection(pos_center, size_char, std::move(text), selected) {}

WidgetBoolean::~WidgetBoolean() {}

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetBoolean::render(SDL_Renderer *renderer) const {

  // ------------------------------------------------------------------------
  // Border -----------------------------------------------------------------
  SDL_Rect border_background;
  border_background.w = _size.w;
  border_background.h = _size.h;
  border_background.x = _position.x;
  border_background.y = _position.y;

  SDL_SetRenderDrawColor(renderer, 69, 71, 90, 200); // Surface1
  SDL_RenderFillRect(renderer, &border_background);
}
