#include "widget_selection.h"
#include "widget_textbox.h"

WidgetSelection::WidgetSelection(kebb::point pos_center, kebb::boxsize size_char, std::string &&text,
                                 bool selected)
    : WidgetTextBox(pos_center, size_char, TextBoxAlign::TB_Center) {

  _color_on = kebb::color(kebb::ColorName::C_Blue);
  _color_off = kebb::color(kebb::ColorName::C_Text);

  move_text(std::move(text));
  set_selected(selected);
}

WidgetSelection::~WidgetSelection() {}

void WidgetSelection::set_selected(bool val) {
  _selected = val;
  _color_text = _selected ? _color_on : _color_off;
}

bool WidgetSelection::is_selected() const { return _selected; }
