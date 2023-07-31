#ifndef WINDOW_GAME_SURVIVAL_H
#define WINDOW_GAME_SURVIVAL_H

#include "window_game.h"
#include <cstdint>

class WindowGameSurvival : public WindowGame {
public:
  WindowGameSurvival(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                     std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                     std::shared_ptr<OptionFile> options);

  virtual ~WindowGameSurvival() override;

  virtual void logic() override;
  virtual void render() override;

private:
  void add_target();
  uint16_t _nb_max_target;
  uint16_t _next_level;
};

#endif // !WINDOW_GAME_SURVIVAL_H
