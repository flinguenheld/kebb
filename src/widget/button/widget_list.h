#ifndef WIDGET_LIST_H
#define WIDGET_LIST_H

#include "widget/button/widget_selection.h"
#include <vector>

class WidgetList : public WidgetSelection {
public:
  WidgetList(point pos_center, boxsize size_char, std::string &&text, std::vector<std::string> &&choices,
             uint16_t choice_index = 0, bool selected = false);
  virtual ~WidgetList();

  std::string current_selection() const;
  void set_selection();

  virtual void action_left();
  virtual void action_right();

private:
  std::vector<std::string> _choices;
};

#endif // !WIDGET_LIST_H
