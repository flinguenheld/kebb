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
      _it(_choices.begin()), _size_char(size_char) {

  init();
}

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text, int16_t range_start,
                       int16_t range_stop, int16_t step, bool selected)

    : WidgetSelection(pos_center, size_char, std::move(text), selected), _size_char(size_char) {

  for (; range_start <= range_stop; range_start += step)
    _choices.emplace_back(std::to_string(range_start));

  _it = _choices.begin();

  init();
}

WidgetList::~WidgetList() {}

void WidgetList::init() {
  // ------------------------------------------------------------------------
  // Geometry ---------------------------------------------------------------

  // Take the longest word
  uint16_t longest_word = 0;
  for (const auto &txt : _choices)
    longest_word = txt.length() > longest_word ? txt.length() : longest_word;

  _space = _size_char.w * 2;
  _position.x -= (_size.w + _space + longest_word) / 2;
  // FIX: _position has to be recalculate

  _size_choice_longest.w = _size_char.w * longest_word; // Ajustable
  _size_choice_longest.h = _size_char.h;

  boxsize size_choices = {static_cast<uint16_t>(_size_char.w * longest_word), _size_char.h};

  _pt_choice_longest.x = _position.x + _size.w + _space + _size_choice_longest.w / 2;
  _pt_choice_longest.y = _position.y;

  _tb_choice = std::make_unique<WidgetTextBox>(_pt_choice_longest, size_choices);
  _tb_choice->set_color_text({148, 226, 213, 200}); // Teal

  display_current_it();
}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
std::string WidgetList::current_selection() const { return *_it; } // TODO: add return
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
  _tb_choice->set_x(_position.x + _size.w + _space + (_size_choice_longest.w - new_width) / 2);
  _tb_choice->set_text(std::move(new_choice));
}
// ------------------------------------------------------------------------
// Render -----------------------------------------------------------------
void WidgetList::render(SDL_Renderer *renderer, TTF_Font *font) const {

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  WidgetTextBox::render(renderer, font);
  // ------------------------------------------------------------------------
  // Choices -----------------------------------------------------------------
  _tb_choice->render(renderer, font);
}
