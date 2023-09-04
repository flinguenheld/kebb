#ifndef WIDGET_LIST_H
#define WIDGET_LIST_H

#include "button/widget_selection.h"
#include <memory>
#include <vector>

/*
 * Based on WidgetSelection, this class add another WidgetTextBox to display a range of strings.
 * Values (string or uint) are stored in a vector of SelectionItem struct (see the mother).
 * Use action_left/action_right methods to change the current value.
 */
class WidgetList : public WidgetSelection {
public:
  WidgetList(widget::point pos_center, widget::boxsize size_char, std::string &&text,
             std::vector<SelectionItem> &&choices, bool selected = false);
  WidgetList(widget::point pos_center, widget::boxsize size_char, std::string &&text, uint16_t range_start,
             uint16_t range_stop, uint16_t step, bool selected = false);
  virtual ~WidgetList() override;

  virtual void action_left() override;
  virtual void action_right() override;

  virtual SelectionItem get_choice() const override;
  virtual void set_choice_by_value(const std::string &value) override;
  virtual void set_choice_by_value(uint16_t value) override;

  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const override;

private:
  void init(widget::point pos_center);

  std::vector<SelectionItem> _choices;
  std::vector<SelectionItem>::iterator _it;
  std::unique_ptr<WidgetTextBox> _tb_choice;

  const widget::boxsize _size_char;
};

#endif // !WIDGET_LIST_H
