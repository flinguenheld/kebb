#ifndef WINDOW_SURVIVAL_MOD_H
#define WINDOW_SURVIVAL_MOD_H

#include "game/window/survival_mod/widget_gauge.h"
#include "game/window/window_game.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <sys/types.h>

struct Level {
  uint16_t waiting_time;
  uint16_t nb_target;
  uint16_t points_next_level;
};

/*
 * Window game survival
 */
class WindowSurvivalMod : public WindowGame {
public:
  WindowSurvivalMod(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                    std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                    std::shared_ptr<OptionFile> options);

  virtual ~WindowSurvivalMod() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  void add_target(uint16_t waiting_time);
  void remove_target();

  std::vector<Level> _levels;

  void up_points();
  int16_t _points;
  uint16_t _price_fail; // Change according to the difficulty
  uint16_t _price_miss;

  uint16_t _previous_miss; // Used for level calculations
  uint16_t _previous_fail;
  uint16_t _previous_success;

  uint16_t _max_fail;
  uint16_t _max_miss;

  std::unique_ptr<WidgetGauge> _widget_gauge;

  virtual void save_record() const override;
};

#endif // !WINDOW_SURVIVAL_MOD_H
