#ifndef WIDGET_TEXTBOX_H
#define WIDGET_TEXTBOX_H

#include "widget_base.h"

class WidgetTextBox : public WidgetBase {

public:
  WidgetTextBox(kebb::point pos, kebb::boxsize size);
  ~WidgetTextBox();
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

  // NOTE: Keep move ?
  void set_text(std::string &&txt);
  void set_color_text(SDL_Color &&color);

protected:
  std::string _text;
  SDL_Color _color_text;
};

#endif // !WIDGET_TEXTBOX_H
