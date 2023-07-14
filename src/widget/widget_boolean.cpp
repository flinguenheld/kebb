#include "widget_boolean.h"
#include "SDL_render.h"
#include "widget/widget_textbox.h"
#include <iostream>

WidgetBoolean::WidgetBoolean(point pos_center, boxsize size_char, std::string &&text, bool selected,
                             bool status)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _status(status) {

  // Catppucin - Mocha
  _color_on = {166, 227, 161, 200}; // Green
  // _color_off = {186, 194, 222, 200};    // Subtext1
  _color_off = {49, 50, 68, 200};       // Surface0
  _color_border = {108, 112, 134, 200}; // Overlay0
  _color_bg = {147, 153, 178, 200};     // Overlay2

  // ------------------------------------------------------------------------
  // Geometry ---------------------------------------------------------------
  _bt_border.w = size_char.w * 6;
  _bt_border.h = size_char.h * 0.85;

  _space_width = size_char.w * 3;
  _total_width = _size.w + _space_width + _bt_border.w;

  _position.x = pos_center.x - _total_width / 2;
  _bt_border.x = _position.x + _size.w + _space_width;
  _bt_border.y = _position.y + (size_char.h - _bt_border.h) / 2;

  // -------------------------------------------
  // ------------------------------
  _bt_background.w = _bt_border.w * 0.90;
  _bt_background.h = _bt_border.h * 0.90;
  _bt_background.x = _bt_border.x + (_bt_border.w - _bt_background.w) / 2;
  _bt_background.y = _bt_border.y + (_bt_border.h - _bt_background.h) / 2;

  _bt_part_left.w = _bt_background.w / 2;
  _bt_part_left.h = _bt_background.h;
  _bt_part_left.x = _bt_background.x;
  _bt_part_left.y = _bt_background.y;

  _bt_part_right.w = _bt_background.w / 2;
  _bt_part_right.h = _bt_background.h;
  _bt_part_right.x = _bt_background.x + _bt_part_left.w;
  _bt_part_right.y = _bt_background.y;
}

WidgetBoolean::~WidgetBoolean() {}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
bool WidgetBoolean::status() const { return _status; }
void WidgetBoolean::set_on() { _status = true; }
void WidgetBoolean::set_off() { _status = false; }

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetBoolean::render(SDL_Renderer *renderer, TTF_Font *font) const {

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  WidgetTextBox::render(renderer, font);

  // ------------------------------------------------------------------------
  // Border -----------------------------------------------------------------
  SDL_SetRenderDrawColor(renderer, _color_border.r, _color_border.g, _color_border.b, _color_border.a);
  SDL_RenderFillRect(renderer, &_bt_border);

  SDL_SetRenderDrawColor(renderer, _color_bg.r, _color_bg.g, _color_bg.b, _color_bg.a);
  SDL_RenderFillRect(renderer, &_bt_background);

  if (_status) {
    SDL_SetRenderDrawColor(renderer, _color_on.r, _color_on.g, _color_on.b, _color_on.a);
    SDL_RenderFillRect(renderer, &_bt_part_right);
  } else {
    SDL_SetRenderDrawColor(renderer, _color_off.r, _color_off.g, _color_off.b, _color_off.a);
    SDL_RenderFillRect(renderer, &_bt_part_left);
  }
}
