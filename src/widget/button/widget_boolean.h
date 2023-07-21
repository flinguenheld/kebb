#ifndef WIDGET_BOOLEAN_H
#define WIDGET_BOOLEAN_H

#include "SDL_render.h"
#include "widget/button/widget_selection.h"
#include "widget/widget_textbox.h"

/*
 * Based on a WidgetSelection which is itself based on WidgetTextBox, this class displays a text and a button
 * ont its right.
 * The status can be changed with the setter and with action_left/right.
 */
class WidgetBoolean : public WidgetSelection {

public:
  WidgetBoolean(kebb::point pos_center, kebb::boxsize size_char, std::string &&text, bool selected = false,
                bool status = false);
  virtual ~WidgetBoolean() override;

  virtual bool get_bool() const override;
  virtual void set_bool(bool val) override;

  virtual void action_left() override;
  virtual void action_right() override;

  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const override;

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
