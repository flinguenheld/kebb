#ifndef WIDGET_SELECTION_H
#define WIDGET_SELECTION_H

#include "SDL_pixels.h"
#include "widget/widget_textbox.h"

/*
 * This widget allows to display a text and set a selected status. This latter changes the text's color.
 * WidgetSelection had been created to work with WidgetWindowSelection which allows to navigate in a vector
 * of WidgetSelection with the up/down arrows.
 */
class WidgetSelection : public WidgetTextBox {
public:
  WidgetSelection(point pos_center, boxsize size_char, std::string &&text, bool selected = false);
  ~WidgetSelection();

  void set_selected(bool val);
  bool is_selected() const;

private:
  bool _selected;
  const SDL_Color _color_on;
  const SDL_Color _color_off;
};

#endif // !WIDGET_SELECTION_H
