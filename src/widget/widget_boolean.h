#ifndef WIDGET_BOOLEAN_H
#define WIDGET_BOOLEAN_H

#include "widget/widget_selection.h"

class WidgetBoolean : public WidgetSelection {

public:
  WidgetBoolean(point pos_center, boxsize size_char, std::string &&text, bool selected = false);
  virtual ~WidgetBoolean();

  virtual void render(SDL_Renderer *renderer) const;

private:
};

#endif // !WIDGET_BOOLEAN_H
