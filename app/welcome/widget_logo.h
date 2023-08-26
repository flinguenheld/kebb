#ifndef WIDGET_LOGO_H
#define WIDGET_LOGO_H

#include "widget_base.h"
#include <functional>
#include <random>
#include <thread>
#include <vector>

/*
 * Render a keyboard (4 lines, 12 columns) and play animations randomly.
 * Launch a thread with update() to use it.
 */
class WidgetLogo : public WidgetBase {
public:
  WidgetLogo(kebb::point position, kebb::boxsize size);
  virtual ~WidgetLogo() override;

  void update();
  void stop();

  virtual void render(SDL_Renderer *renderer) const override;

private:
  std::vector<std::vector<uint16_t>> _tab;
  const uint16_t _nb_colums;
  const uint16_t _nb_lines;

  kebb::boxsize _key_size;

  uint16_t _border_thickness;
  uint16_t _space_w;
  uint16_t _space_h;

  bool _continue;
  uint16_t _type_animation;

  // --
  std::random_device _seed;
  std::mt19937 _engine;

  // --
  SDL_Color _color_border;
  SDL_Color _color_key;
  SDL_Color _color_current;
};

#endif // !WIDGET_LOGO_H
