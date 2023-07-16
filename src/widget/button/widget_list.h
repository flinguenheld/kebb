#ifndef WIDGET_LIST_H
#define WIDGET_LIST_H

#include "renderer.h"
#include "utils.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_textbox.h"
#include <algorithm>
#include <memory>
#include <vector>

/*
 * Based on WidgetSelection, this class add another WidgetTextBox to display an range of strings.
 * Values are stored in a vector of SelectionItem struct (see the mother).
 * Use action_left/action_right methods to change the current value.
 */
class WidgetList : public WidgetSelection {
public:
  WidgetList(point pos_center, boxsize size_char, std::string &&text, std::vector<SelectionItem> &&choices,
             bool selected = false);
  WidgetList(point pos_center, boxsize size_char, std::string &&text, int16_t range_start, int16_t range_stop,
             int16_t step, bool selected = false);
  virtual ~WidgetList();

  virtual void action_left();
  virtual void action_right();

  virtual SelectionItem get_choice() const;
  virtual void set_choice_by_value(const std::string &value);

  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

private:
  void init(point pos_center);

  std::vector<SelectionItem> _choices;
  std::vector<SelectionItem>::iterator _it;
  std::unique_ptr<WidgetTextBox> _tb_choice;
  void display_current_it();

  uint16_t _longest_choice_width;
  uint16_t _space;

  const boxsize _size_char;
};

#endif // !WIDGET_LIST_H
