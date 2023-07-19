#include "controller.h"

Controller::Controller() : _circumflex(false), _grave(false), _diaeresis(false), _mask_mod(0x3FF) {}

void Controller::handle_input(bool &running, std::shared_ptr<WidgetWindow> window) {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {

    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {

      switch (e.key.keysym.sym) {

      case SDLK_ESCAPE:
        window->control_escape();
        break;

      case SDLK_RETURN:
      case SDLK_RETURN2: // NOTE: What is that ?
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
        // check_targets(targets, convert_us(e));
        window->control_others(convert_us(e));
        // check_targets(targets, convert_fr(e));
      }
    }
  }
}

/*
 * Convert the current SDL keycode event to the Kebb keycode for the US version.
 * Return the keycode or 0 (0 is not count as a fail by WindowGame).
 * It uses these keycodes:
 *      https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_us.h
 *
 * And these ones for the french accents:
 *      https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_us_extended.h
 */
uint16_t Controller::convert_us(SDL_Event &e) {

  const auto mask = 0x3FF; // Remove the first sixth bits (NUM/CAP/GUI)
                           // std::cout << "mode: " << (e.key.keysym.mod & mask) << std::endl;

  // clang-format off

  // --------------------------------------------------
  // French specials ----------------------------------
  if (_circumflex) {
    _circumflex = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case SDLK_a:       return 2104; // Â
        case SDLK_e:       return 2105; // Ê
        case SDLK_i:       return 2106; // Î
        case SDLK_o:       return 2107; // Ô
        case SDLK_u:       return 2108; // Û
      }
    } else {
      switch (e.key.keysym.sym) {
        case SDLK_a:       return 2004; // â
        case SDLK_e:       return 2005; // ê
        case SDLK_i:       return 2006; // î
        case SDLK_o:       return 2007; // ô
        case SDLK_u:       return 2008; // û
      }
    }
  } else if (_grave) {
    _grave = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case SDLK_a:       return 2101; // À
        case SDLK_e:       return 2102; // È
        case SDLK_u:       return 2103; // Ù
      }
    } else {
      switch (e.key.keysym.sym) {
        case SDLK_a:       return 2001; // à
        case SDLK_e:       return 2002; // è
        case SDLK_u:       return 2003; // ù
      }
    }
  } else if (_diaeresis) {
    _diaeresis = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case SDLK_i:       return 2109; // Ï
        case SDLK_e:       return 2110; // Ë
        case SDLK_u:       return 2111; // Ü
      }
    } else {
      switch (e.key.keysym.sym) {
        case SDLK_i:       return 2009; // Ï
        case SDLK_e:       return 2010; // Ë
        case SDLK_u:       return 2011; // Ü
      }
    }
  }

  // --------------------------------------------------
  // --------------------------------------------------
  if ((e.key.keysym.mod & _mask_mod) == KMOD_NONE) {
    switch (e.key.keysym.sym) {
      case SDLK_a:      return 10;
      case SDLK_b:      return 11;
      case SDLK_c:      return 12;
      case SDLK_d:      return 13;
      case SDLK_e:      return 14;
      case SDLK_f:      return 15;
      case SDLK_g:      return 16;
      case SDLK_h:      return 17;
      case SDLK_i:      return 18;
      case SDLK_j:      return 19;
      case SDLK_k:      return 20;
      case SDLK_l:      return 21;
      case SDLK_m:      return 22;
      case SDLK_n:      return 23;
      case SDLK_o:      return 24;
      case SDLK_p:      return 25;
      case SDLK_q:      return 26;
      case SDLK_r:      return 27;
      case SDLK_s:      return 28;
      case SDLK_t:      return 29;
      case SDLK_u:      return 30;
      case SDLK_v:      return 31;
      case SDLK_w:      return 32;
      case SDLK_x:      return 33;
      case SDLK_y:      return 34;
      case SDLK_z:      return 35;

      case SDLK_0: case SDLK_KP_0:    return 500;
      case SDLK_1: case SDLK_KP_1:    return 501;
      case SDLK_2: case SDLK_KP_2:    return 502;
      case SDLK_3: case SDLK_KP_3:    return 503;
      case SDLK_4: case SDLK_KP_4:    return 504;
      case SDLK_5: case SDLK_KP_5:    return 505;
      case SDLK_6: case SDLK_KP_6:    return 506;
      case SDLK_7: case SDLK_KP_7:    return 507;
      case SDLK_8: case SDLK_KP_8:    return 508;
      case SDLK_9: case SDLK_KP_9:    return 509;

      case SDLK_BACKQUOTE:            return 1009;
      case SDLK_QUOTE:                return 1001;
      case SDLK_COMMA:                return 1012;
      case SDLK_MINUS:                return 1013;
      case SDLK_PERIOD:               return 1014;
      case SDLK_SLASH:                return 1015;
      case SDLK_SEMICOLON:            return 1017;
      case SDLK_EQUALS:               return 1019;
      case SDLK_LEFTBRACKET:          return 1023;
      case SDLK_RIGHTBRACKET:         return 1025;
      case SDLK_BACKSLASH:            return 1024;
    }
  }

  if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {

    if ((e.key.keysym.mod & KMOD_RALT) == KMOD_RALT){
        switch (e.key.keysym.sym) {
          case SDLK_e:      return 2100; // É
          case SDLK_z:      return 2112; // Æ
          case SDLK_k:                   // There are two Œ :|
          case SDLK_x:      return 2113; // Œ
          case SDLK_COMMA:  return 2114; // Ç

          case SDLK_QUOTE:            _diaeresis = true; return 0;
        }
    }

    switch (e.key.keysym.sym) {
      case SDLK_a:      return 100;
      case SDLK_b:      return 101;
      case SDLK_c:      return 102;
      case SDLK_d:      return 103;
      case SDLK_e:      return 104;
      case SDLK_f:      return 105;
      case SDLK_g:      return 106;
      case SDLK_h:      return 107;
      case SDLK_i:      return 108;
      case SDLK_j:      return 109;
      case SDLK_k:      return 110;
      case SDLK_l:      return 111;
      case SDLK_m:      return 112;
      case SDLK_n:      return 113;
      case SDLK_o:      return 114;
      case SDLK_p:      return 115;
      case SDLK_q:      return 116;
      case SDLK_r:      return 117;
      case SDLK_s:      return 118;
      case SDLK_t:      return 119;
      case SDLK_u:      return 120;
      case SDLK_v:      return 121;
      case SDLK_w:      return 122;
      case SDLK_x:      return 123;
      case SDLK_y:      return 124;
      case SDLK_z:      return 125;

      case SDLK_BACKQUOTE:       return 1028; // ~
      case SDLK_1:               return 1000; // !
      case SDLK_2:               return 1022; // @
      case SDLK_3:               return 1002; // #
      case SDLK_4:               return 1004; // $
      case SDLK_5:               return 1003; // %
      case SDLK_6:               return 1026; // ^
      case SDLK_7:               return 1005; // &
      case SDLK_8:               return 1010; // *
      case SDLK_9:               return 1007; // (
      case SDLK_0:               return 1008; // )
      case SDLK_MINUS:           return 1027; // _
      case SDLK_EQUALS:          return 1011; // +
      case SDLK_LEFTBRACKET:     return 1029; // {
      case SDLK_RIGHTBRACKET:    return 1030; // }
      case SDLK_BACKSLASH:       return 1031; // |
      case SDLK_SEMICOLON:       return 1016; // :
      case SDLK_QUOTE:           return 1006; // "
      case SDLK_COMMA:           return 1018; // <
      case SDLK_PERIOD:          return 1020; // >
      case SDLK_SLASH:           return 1021; // ?
    }
  }

  if ((e.key.keysym.mod & KMOD_RALT) == KMOD_RALT) {
    switch (e.key.keysym.sym) {
      case SDLK_e:      return 2000; // é
      case SDLK_z:      return 2012; // æ
      case SDLK_k:                   // There are two Œ :|
      case SDLK_x:      return 2013; // œ
      case SDLK_COMMA:  return 2014; // ç
      case SDLK_5:      return 2015; // €

      case SDLK_6:            _circumflex = true; return 0;
      case SDLK_BACKQUOTE:    _grave = true; return 0;
    }
  }

  return 0;
}
