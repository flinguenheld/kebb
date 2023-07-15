#include "widget_list.h"
#include "renderer.h"
#include "utils.h"
#include "widget/widget_textbox.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <vector>

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text,
                       std::vector<std::string> &&choices, bool selected)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _choices(std::move(choices)),
      _it(_choices.begin()), _size_char(size_char), _longest_choice_width(0), _space(0) {

  init(pos_center);
}

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text, int16_t range_start,
                       int16_t range_stop, int16_t step, bool selected)

    : WidgetSelection(pos_center, size_char, std::move(text), selected), _size_char(size_char),
      _longest_choice_width(0), _space(0) {

  for (; range_start <= range_stop; range_start += step)
    _choices.emplace_back(std::to_string(range_start));

  _it = _choices.begin();

  init(pos_center);
}

WidgetList::~WidgetList() {}

void WidgetList::init(point pos_center) {

  // Geometry --
  // Find the longest word
  for (const auto &txt : _choices) {
    if (txt.length() * _size_char.w > _longest_choice_width)
      _longest_choice_width = txt.length() * _size_char.w;
  }

  _space = _size_char.w * 2;

  // Set the global position with the widest choice
  _position.x = pos_center.x - (_size.w + _space + _longest_choice_width) / 2;

  // The _tb_choice position and width will be updated by display_current_it()
  boxsize size_choices = {_longest_choice_width, _size_char.h};
  _tb_choice = std::make_unique<WidgetTextBox>(_position, size_choices);
  _tb_choice->set_color_text({148, 226, 213, 200}); // Teal
  display_current_it();
}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
std::string WidgetList::current_selection() const { return *_it; }
void WidgetList::set_selection(const std::string &text) {

  _it = std::find(_choices.begin(), _choices.end(), text);
  display_current_it();
}

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
  std::string new_choice(*_it);

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
