#ifndef WIDGET_TEXTBOX_H
#define WIDGET_TEXTBOX_H

#include "widget_base.h"

class WidgetTextBox : public WidgetBase {

public:
  WidgetTextBox(point pos, boxsize size);
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

  // NOTE: Keep move ?
  void set_text(std::string &&txt);

protected:
  std::string _text;
  SDL_Color _color_text;
};

#endif // !WIDGET_TEXTBOX_H
