#ifndef WIDGET_BOOLEAN_H
#define WIDGET_BOOLEAN_H

#include "widget/widget_selection.h"
#include <cstdint>

class WidgetBoolean : public WidgetSelection {

public:
  WidgetBoolean(point pos_center, boxsize size_char, std::string &&text, bool selected = false,
                bool status = false);
  virtual ~WidgetBoolean();

  bool status() const;
  void set_on();
  void set_off();

  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

private:
  bool _status;

  SDL_Color _color_on;
  SDL_Color _color_off;
  SDL_Color _color_border;
  SDL_Color _color_bg;

  uint16_t _space_width;
  uint16_t _total_width; // Textbox + space + button

  SDL_Rect _bt_border;
  SDL_Rect _bt_background; // Not rendered
  SDL_Rect _bt_part_left;
  SDL_Rect _bt_part_right;
};

#endif // !WIDGET_BOOLEAN_H
