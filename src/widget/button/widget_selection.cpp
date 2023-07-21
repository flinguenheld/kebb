#include "widget_selection.h"

// clang-format off
WidgetSelection::WidgetSelection(kebb::point pos_center, kebb::boxsize size_char, std::string &&text, bool selected)
    : WidgetTextBox(pos_center, size_char)
{
  // clang-format on

  _color_on = kebb::color(kebb::ColorName::C_Blue);
  _color_off = kebb::color(kebb::ColorName::C_Text);

  set_text(std::move(text));
  set_selected(selected);

  _size.w = size_char.w * _text.length();
  _position.x -= _size.w / 2;
  _position.y -= _size.h / 2;
}

WidgetSelection::~WidgetSelection() {}

void WidgetSelection::set_selected(bool val) {
  _selected = val;
  _color_text = _selected ? _color_on : _color_off;
}

bool WidgetSelection::is_selected() const { return _selected; }
