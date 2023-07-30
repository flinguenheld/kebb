#ifndef WINDOW_GAME_SURVIVAL_H
#define WINDOW_GAME_SURVIVAL_H

#include "window_game.h"

class WindowGameSurvival : public WindowGame {
public:
  WindowGameSurvival(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                     std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                     std::shared_ptr<OptionFile> options);

  virtual ~WindowGameSurvival() override;

  virtual void render() override;
};

#endif // !WINDOW_GAME_SURVIVAL_H
