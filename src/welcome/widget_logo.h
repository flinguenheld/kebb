#ifndef WIDGET_LOGO_H
#define WIDGET_LOGO_H

#include "utils.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <random>
#include <sys/types.h>
#include <vector>

/*
 * Render a keyboard (4 lines, 12 columns) and play randomly animations.
 * Launch a thread with update() to use it.
 */
class WidgetLogo : public WidgetBase {
public:
  WidgetLogo(point position, boxsize size);
  virtual ~WidgetLogo();

  void update();
  void stop();

  virtual void render(SDL_Renderer *renderer) const;

private:
  std::vector<std::vector<uint16_t>> _tab;
  const uint16_t _nb_cases;
  const uint16_t _nb_lines;

  boxsize _key_size;

  uint16_t _border_thickness;
  uint16_t _space_w;
  uint16_t _space_h;

  bool _continue;
  uint16_t _type_animation;
  uint8_t _r, _g, _b;

  // --
  std::random_device _seed;
  std::mt19937 _engine;
};

#endif // !WIDGET_LOGO_H
