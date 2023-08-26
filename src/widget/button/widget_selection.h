#ifndef WIDGET_SELECTION_H
#define WIDGET_SELECTION_H

#include "widget_textbox.h"

// Use by child WidgetList
struct SelectionItem {
  std::string text;
  std::string value_string = "";
  uint16_t value_uint = 0;
};

/*
 * This widget allows to display a text and set a selected status. This latter changes the text's color.
 * WidgetSelection had been created to work with WidgetWindowSelection which allows to navigate in a vector
 * of WidgetSelection with the up/down arrows.
 */
class WidgetSelection : public WidgetTextBox {
public:
  WidgetSelection(kebb::point pos_center, kebb::boxsize size_char, std::string &&text, bool selected = false);
  virtual ~WidgetSelection() override;

  void set_selected(bool val);
  bool is_selected() const;

  virtual void action_left(){};
  virtual void action_right(){};

  virtual bool get_bool() const { return false; };
  virtual void set_bool(bool val){};

  virtual SelectionItem get_choice() const { return {"", "", 0}; };
  virtual void set_choice_by_value(const std::string &value){};
  virtual void set_choice_by_value(uint16_t value){};

protected:
  bool _selected;
  SDL_Color _color_on;
  SDL_Color _color_off;
};

#endif // !WIDGET_SELECTION_H
