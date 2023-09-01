#include "widget_list.h"

WidgetList::WidgetList(widget::point pos_center, widget::boxsize size_char, std::string &&text,
                       std::vector<SelectionItem> &&choices, bool selected)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _choices(std::move(choices)),
      _it(_choices.begin()), _size_char(size_char) {

  init(pos_center);
}

WidgetList::WidgetList(widget::point pos_center, widget::boxsize size_char, std::string &&text,
                       uint16_t range_start, uint16_t range_stop, uint16_t step, bool selected)

    : WidgetSelection(pos_center, size_char, std::move(text), selected), _size_char(size_char) {

  for (; range_start <= range_stop; range_start += step)
    _choices.emplace_back(SelectionItem{.text = std::to_string(range_start), .value_uint = range_start});

  _it = _choices.begin();

  init(pos_center);
}

WidgetList::~WidgetList() {}

void WidgetList::init(widget::point pos_center) {

  uint16_t longest_choice_width = 0;

  // Geometry --
  // Find the longest choice
  for (const auto &item : _choices) {
    if (item.text.length() * _size_char.w > longest_choice_width)
      longest_choice_width = item.text.length() * _size_char.w;
  }

  // Set text positions with the widest choice
  const uint16_t space = _size_char.w * 2;
  const uint16_t width_total = _size.w + space + longest_choice_width;
  const uint16_t x_left = pos_center.x - width_total / 2;

  _position.x = x_left + _size.w / 2;
  widget::point pt_choices = {static_cast<uint16_t>(x_left + _size.w + space + longest_choice_width / 2),
                            pos_center.y};

  // Create the second textbox
  widget::boxsize size_choices = {longest_choice_width, _size_char.h};
  _tb_choice = std::make_unique<WidgetTextBox>(pt_choices, _size_char, TextBoxAlign::TB_Center);
  _tb_choice->set_color_text(widget::color(widget::ColorName::C_Teal));
}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
void WidgetList::set_choice_by_value(const std::string &value) {

  _it = _choices.begin();
  while (_it != _choices.end()) {

    if ((*_it).value_string == value) {
      _tb_choice->set_text((*_it).text);
      return;
    }
    ++_it;
  }

  _it = _choices.begin();
}

void WidgetList::set_choice_by_value(uint16_t value) { // TODO: Rewrite both ?

  _it = _choices.begin();
  while (_it != _choices.end()) {

    if ((*_it).value_uint == value) {
      _tb_choice->set_text((*_it).text);
      return;
    }
    ++_it;
  }

  _it = _choices.begin();
}

SelectionItem WidgetList::get_choice() const { return *_it; }

void WidgetList::action_left() {

  if (_it == _choices.begin())
    _it = _choices.end();

  --_it;

  _tb_choice->set_text((*_it).text);
}
void WidgetList::action_right() {

  ++_it;
  if (_it == _choices.end())
    _it = _choices.begin();

  _tb_choice->set_text((*_it).text);
}

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetList::render(SDL_Renderer *renderer, TTF_Font *font) const {
  _tb_choice->render(renderer, font);
  WidgetTextBox::render(renderer, font);
}
