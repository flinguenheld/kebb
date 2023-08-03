#ifndef WINDOW_GAME_TIMER_H
#define WINDOW_GAME_TIMER_H

#include "window_game.h"

class WindowGameTimer : public WindowGame {
public:
  WindowGameTimer(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                  std::shared_ptr<Renderer> renderer, std::shared_ptr<Score> score,
                  std::shared_ptr<OptionFile> options);

  virtual ~WindowGameTimer() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  uint16_t _countdown_value; // Seconds
};

#endif // !WINDOW_GAME_TIMER_H
