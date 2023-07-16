#ifndef WIDGET_BOOLEAN_H
#define WIDGET_BOOLEAN_H

#include "SDL_render.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_textbox.h"

/*
 * Based on a WidgetSelection which is itself based on WidgetTextBox, this class displays a text and a button
 * ont its right.
 * The status can be changed with the setter and with action_left/right for polymorphism.
 */
class WidgetBoolean : public WidgetSelection {

public:
  WidgetBoolean(point pos_center, boxsize size_char, std::string &&text, bool selected = false,
                bool status = false);
  virtual ~WidgetBoolean();

  virtual void set_value(int16_t val);
  virtual int16_t get_value() const;

  virtual void action_left();
  virtual void action_right();

  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

private:
  bool _status;

  SDL_Color _color_bt_on;
  SDL_Color _color_bt;
  SDL_Color _color_border;
  SDL_Color _color_bg;

  uint16_t _space_width;
  uint16_t _total_width; // Textbox + space + button

  SDL_Rect _bt_border;
  SDL_Rect _bt_background;
  SDL_Rect _bt_part_left;
  SDL_Rect _bt_part_right;
};

#endif // !WIDGET_BOOLEAN_H
