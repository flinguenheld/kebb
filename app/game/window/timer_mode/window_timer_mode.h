#ifndef WINDOW_TIMER_MODE_H
#define WINDOW_TIMER_MODE_H

#include "file_layout.h"
#include "game/window/window_game.h"
#include <cstdint>

class WindowTimerMode : public WindowGame {
public:
  WindowTimerMode(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                  std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records,
                  std::shared_ptr<OptionFile> options, std::shared_ptr<LayoutFile> layouts);

  virtual ~WindowTimerMode() override;

  virtual void logic() override;
  virtual void render() const override;

private:
  uint16_t _countdown_value; // Seconds

  virtual void save_record() const override;
};

#endif // !WINDOW_TIMER_MODE_H
