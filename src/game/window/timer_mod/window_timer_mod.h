#ifndef WINDOW_TIMER_MOD_H
#define WINDOW_TIMER_MOD_H

#include "game/window/window_game.h"

class WindowTimerMod : public WindowGame {
public:
  WindowTimerMod(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                 std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records,
                 std::shared_ptr<OptionFile> options);

  virtual ~WindowTimerMod() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  uint16_t _countdown_value; // Seconds

  virtual void save_record() const override;
};

#endif // !WINDOW_TIMER_MOD_H
