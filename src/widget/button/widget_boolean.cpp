#include "widget_boolean.h"

WidgetBoolean::WidgetBoolean(widget::point pos_center, widget::boxsize size_char, std::string &&text,
                             bool selected, bool status)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _status(status) {

  _color_bt_on = widget::color(widget::ColorName::C_Sky);
  _color_bt = widget::color(widget::ColorName::C_Surface0);
  _color_bg = widget::color(widget::ColorName::C_Surface2);
  _color_border = widget::color(widget::ColorName::C_Surface1);

  // ------------------------------------------------------------------------
  // Geometry ---------------------------------------------------------------
  _bt_border.w = size_char.w * 6;
  _bt_border.h = size_char.h * 0.85;

  const uint16_t _space_width = size_char.w * 2;
  const uint16_t _total_width = _size.w + _space_width + _bt_border.w;
  const uint16_t x_left = pos_center.x - _total_width / 2;

  _position.x = x_left + _size.w / 2; // Text position

  // Button --
  _bt_border.x = x_left + _size.w + _space_width;
  _bt_border.y = _position.y - _size.h * 0.4;

  _bt_background.w = _bt_border.w * 0.90;
  _bt_background.h = _bt_border.h * 0.80;
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
bool WidgetBoolean::get_bool() const { return _status; }
void WidgetBoolean::set_bool(bool val) { _status = val; }

void WidgetBoolean::action_left() { _status = false; }
void WidgetBoolean::action_right() { _status = true; }

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetBoolean::render(SDL_Renderer *renderer, TTF_Font *font) const {

  if (_visible) {
    // ------------------------------------------------------------------------
    // Text -------------------------------------------------------------------
    WidgetTextBox::render(renderer, font);

    // ------------------------------------------------------------------------
    // Button -----------------------------------------------------------------
    if (_selected)
      SDL_SetRenderDrawColor(renderer, _color_on.r, _color_on.g, _color_on.b, _color_on.a);
    else
      SDL_SetRenderDrawColor(renderer, _color_border.r, _color_border.g, _color_border.b, _color_border.a);
    SDL_RenderFillRect(renderer, &_bt_border);

    SDL_SetRenderDrawColor(renderer, _color_bg.r, _color_bg.g, _color_bg.b, _color_bg.a);
    SDL_RenderFillRect(renderer, &_bt_background);

    if (_status) {
      SDL_SetRenderDrawColor(renderer, _color_bt_on.r, _color_bt_on.g, _color_bt_on.b, _color_bt_on.a);
      SDL_RenderFillRect(renderer, &_bt_part_right);
      SDL_SetRenderDrawColor(renderer, _color_bt.r, _color_bt.g, _color_bt.b, _color_bt.a);
      SDL_RenderFillRect(renderer, &_bt_part_left);
    } else {
      SDL_SetRenderDrawColor(renderer, _color_bt.r, _color_bt.g, _color_bt.b, _color_bt.a);
      SDL_RenderFillRect(renderer, &_bt_part_right);
    }
  }
}
