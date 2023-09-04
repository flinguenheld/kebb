#include "widget_base.h"

WidgetBase::WidgetBase(widget::point position, widget::boxsize size)
    : _position(position), _size(size), _color({255, 255, 255, 1}), _visible(true) {}
WidgetBase::~WidgetBase() {}

widget::point WidgetBase::position() const { return _position; };
widget::boxsize WidgetBase::size() const { return _size; }
SDL_Color WidgetBase::color() const { return _color; }

void WidgetBase::set_size(const widget::boxsize &s) { _size = s; }
void WidgetBase::set_color(const SDL_Color &c) { _color = c; }
void WidgetBase::set_visible(bool v) { _visible = v; }

void WidgetBase::set_x(uint16_t x) { _position.x = x; }
void WidgetBase::set_y(uint16_t y) { _position.y = y; }
void WidgetBase::set_w(uint16_t w) { _size.w = w; }
void WidgetBase::set_h(uint16_t h) { _size.h = h; }
