#ifndef LOOP_H
#define LOOP_H

#include "about/window_about.h"
#include "controller.h"
#include "file_layout.h"
#include "file_option.h"
#include "file_record.h"
#include "game/window/survival_mode/window_survival_mode.h"
#include "game/window/survival_mode/window_welcome_survival.h"
#include "game/window/timer_mode/window_timer_mode.h"
#include "game/window/timer_mode/window_welcome_timer.h"
#include "game/window/window_gameover.h"
#include "option/window_option.h"
#include "record/window_record.h"
#include "welcome/window_welcome.h"

class Loop {
public:
  Loop(kebb::boxsize screen_size, std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options,
       std::shared_ptr<LayoutFile> layouts);

  void run(Controller &controller);

private:
  std::shared_ptr<WidgetWindow> _current_window; // Shared with the controller

  std::shared_ptr<RecordFile> _records; // Created here to avoid repetitive read/write actions
  std::shared_ptr<OptionFile> _options;
  std::shared_ptr<LayoutFile> _layouts;

  std::shared_ptr<Renderer> _renderer;
  const kebb::boxsize _screen_size;
};

#endif
