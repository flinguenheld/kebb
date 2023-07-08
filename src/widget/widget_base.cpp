#include "widget_base.h"

WidgetBase::WidgetBase(point position, boxsize size) : _position(position), _size(size) {}

SDL_Color WidgetBase::color() const { return _color; }
point WidgetBase::position() const { return _position; };
boxsize WidgetBase::size() const { return _size; }
