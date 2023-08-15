#include "controller.h"

Controller::Controller(std::shared_ptr<LayoutFile> layouts)
    : _layouts(layouts), _dead_key(0), _dead_key_deactivation(false) {}

void Controller::handle_input(bool &running, std::shared_ptr<WidgetWindow> window) {

  SDL_Event e;
  while (SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE) { // TODO: Confirm mouse click on X
      running = false;

    } else if (e.type == SDL_KEYDOWN) {

      switch (e.key.keysym.sym) {

      case SDLK_ESCAPE:
        window->control_escape();
        break;

      case SDLK_RETURN:
      case SDLK_RETURN2:
      case SDLK_KP_ENTER:
        window->control_enter();
        break;

      case SDLK_UP:
        window->control_up();
        break;

      case SDLK_DOWN:
        window->control_down();
        break;

      case SDLK_LEFT:
        window->control_left();
        break;

      case SDLK_RIGHT:
        window->control_right();
        break;

      case SDLK_LSHIFT:
      case SDLK_RSHIFT:
      case SDLK_LALT:
      case SDLK_RALT:
      case SDLK_LCTRL:
      case SDLK_RCTRL:
      case SDLK_LGUI:
      case SDLK_RGUI:
        break;

      default:

#ifdef DEBUG
        std::cout << "--------------------------------------------------" << std::endl;
        std::cout << "mode: " << e.key.keysym.mod << std::endl;
        std::cout << "keysym: " << e.key.keysym.sym << std::endl;
#endif

        const bool shift = (e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT ||
                           (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT;
        const bool alt = (e.key.keysym.mod & KMOD_LALT) == KMOD_LALT;
        const bool ralt = (e.key.keysym.mod & KMOD_RALT) == KMOD_RALT;

        for (const auto &k : _layouts->keys()) {

          if (k.shift == shift && k.alt == alt && k.altgr == ralt) {
            if (e.key.keysym.sym == k.sym) {

              if (k.is_dead != 0) {
                _dead_key = k.is_dead;
                break;
              }

              if (_dead_key == 0 || (_dead_key != 0 && k.dead == _dead_key)) {
                window->control_others(k.text);
                break;
              }
            }
          }
        }

        // The dead key has to run only for the next key.
        if (_dead_key != 0) {
          if (_dead_key_deactivation) {
            _dead_key = 0;
            _dead_key_deactivation = false;
          } else
            _dead_key_deactivation = true;
        }
      }
    }
  }
}
