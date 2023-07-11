#include "widget_base.h"

WidgetBase::WidgetBase(point position, boxsize size)
    : _position(position), _size(size), _color({255, 255, 255, 1}) {}

point WidgetBase::position() const { return _position; };
boxsize WidgetBase::size() const { return _size; }
SDL_Color WidgetBase::color() const { return _color; }

void WidgetBase::set_position(const point &p) { _position = p; }
void WidgetBase::set_size(const boxsize &s) { _size = s; }
void WidgetBase::set_color(const SDL_Color &c) { _color = c; }
