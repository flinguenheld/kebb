#ifndef WIDGET_LOGO_H
#define WIDGET_LOGO_H

#include "utils.h"
#include "widget/widget_base.h"
#include <cstdint>
#include <random>
#include <sys/types.h>
#include <vector>

class WidgetLogo : public WidgetBase {
public:
  WidgetLogo(point position, boxsize size);
  virtual ~WidgetLogo();

  void update();
  void stop();
  virtual void render(SDL_Renderer *renderer, TTF_Font *font) const;

private:
  std::vector<std::vector<int16_t>> _tab;
  const uint16_t _nb_cases;
  const uint16_t _nb_lines;

  boxsize _key_size;

  uint16_t _border_thickness;
  uint16_t _space_w;
  uint16_t _space_h;

  bool _continue;
  void fill(uint8_t line, uint8_t column_start);
  // --
  std::random_device _seed;
  std::mt19937 _engine;

  std::uniform_int_distribution<uint16_t> random_line;
  std::uniform_int_distribution<uint16_t> random_case;
};

#endif // !WIDGET_LOGO_H
