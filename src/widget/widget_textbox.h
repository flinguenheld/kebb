#ifndef WIDGET_TEXTBOX_H
#define WIDGET_TEXTBOX_H

#include "utils.h"
#include "widget_base.h"
enum class TextBoxAlign {
  TB_Left,
  TB_Center,
};

class WidgetTextBox : public WidgetBase {

public:
  WidgetTextBox(kebb::point pos, kebb::boxsize char_size);
  WidgetTextBox(kebb::point position, kebb::boxsize char_size, TextBoxAlign alignment);
  WidgetTextBox(kebb::point position, kebb::boxsize char_size, TextBoxAlign alignment, std::string &&text,
                SDL_Color &&color_text);
  virtual ~WidgetTextBox() override;
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const override;

  void move_text(std::string &&txt); // NOTE: Keep move ?
  void set_text(std::string txt);
  void set_color_text(SDL_Color &&color);
  std::string get_text() const;

protected:
  std::string _text;
  SDL_Color _color_text;

  TextBoxAlign _alignment;
  kebb::boxsize _char_size;
};

#endif // !WIDGET_TEXTBOX_H
