#include "widget_list.h"
#include "widget/button/widget_selection.h"
#include <algorithm>

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text,
                       std::vector<SelectionItem> &&choices, bool selected)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _choices(std::move(choices)),
      _it(_choices.begin()), _size_char(size_char), _longest_choice_width(0), _space(0) {

  init(pos_center);
}

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text, int16_t range_start,
                       int16_t range_stop, int16_t step, bool selected)

    : WidgetSelection(pos_center, size_char, std::move(text), selected), _size_char(size_char),
      _longest_choice_width(0), _space(0) {

  for (; range_start <= range_stop; range_start += step)
    _choices.emplace_back(SelectionItem{std::to_string(range_start), std::to_string(range_start)});

  _it = _choices.begin();

  init(pos_center);
}

WidgetList::~WidgetList() {}

void WidgetList::init(point pos_center) {

  // Geometry --
  // Find the longest word
  for (const auto &item : _choices) {
    if (item.text.length() * _size_char.w > _longest_choice_width)
      _longest_choice_width = item.text.length() * _size_char.w;
  }

  _space = _size_char.w * 2;

  // Set the global position with the widest choice
  _position.x = pos_center.x - (_size.w + _space + _longest_choice_width) / 2;

  // The _tb_choice position and width will be updated by display_current_it()
  boxsize size_choices = {_longest_choice_width, _size_char.h};
  _tb_choice = std::make_unique<WidgetTextBox>(_position, size_choices);
  _tb_choice->set_color_text(kebb::color(kebb::ColorName::C_Teal));
  display_current_it();
}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
void WidgetList::set_choice_by_value(const std::string &value) {

  _it = _choices.begin();
  while (_it != _choices.end()) {

    if ((*_it).value == value) {
      display_current_it();
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

  display_current_it();
}
void WidgetList::action_right() {

  ++_it;
  if (_it == _choices.end())
    _it = _choices.begin();

  display_current_it();
}

/*
 * Take the current text, resize tb_choice and set the text.
 */
void WidgetList::display_current_it() {
  std::string new_choice((*_it).text);

  uint16_t new_width = new_choice.length() * _size_char.w;

  _tb_choice->set_w(new_width);
  _tb_choice->set_x(_position.x + _size.w + _space + (_longest_choice_width - new_width) / 2);
  _tb_choice->set_text(std::move(new_choice));
}

// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetList::render(SDL_Renderer *renderer, TTF_Font *font) const {
  _tb_choice->render(renderer, font);
  WidgetTextBox::render(renderer, font);
}
