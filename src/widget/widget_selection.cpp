#include "widget_selection.h"

// clang-format off
WidgetSelection::WidgetSelection(point pos_center, boxsize size_char, std::string &&text, bool selected)
    : WidgetTextBox(pos_center, size_char),

    // _color_on({250, 179, 135, 200}), // Peach
    // _color_on({148, 226, 213, 200}), // Teal
    _color_on({137, 180, 250, 200}), // Blue
    _color_off({205, 214, 244, 200}) // Text

{
  // clang-format on

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
