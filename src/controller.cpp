#include "controller.h"
#include "file/layout_file.h"

Controller::Controller(std::shared_ptr<LayoutFile> layouts)
    : _layouts(layouts), _dead_key(0), _dead_key_deactivation(false), _circumflex(false), _grave(false),
      _diaeresis(false), _mask_mod(0x3FF) {} // FIX: Clean

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

        const bool shift = (e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT ||
                           (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT;
        const bool alt = (e.key.keysym.mod & KMOD_LALT) == KMOD_LALT;
        const bool ralt = (e.key.keysym.mod & KMOD_RALT) == KMOD_RALT;

        for (const auto &k : _layouts->keys()) {

          if (k.shift == shift && k.alt == alt && k.altgr == ralt) {
            if (e.key.keysym.sym == k.sym) {

              if (k.is_dead) {
                _dead_key = k.is_dead; // FIX: find a way to manage
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

// ----------------------------------------------------------------------------------------------------
// QWERTY ---------------------------------------------------------------------------------------------
/*
 * Convert the current SDL keycode event to the Kebb keycode for the US version.
 * Return the keycode or 0 (0 is not count as a fail by WindowGame).
 * It uses these keycodes:
 *      https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_us.h
 *
 * And these ones for the french extras:
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
          case SDLK_z:      return 2113; // Æ
          case SDLK_k:                   // There are two Œ :|
          case SDLK_x:      return 2114; // Œ
          case SDLK_COMMA:  return 2112; // Ç

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
      case SDLK_z:      return 2014; // æ
      case SDLK_k:                   // There are two Œ :|
      case SDLK_x:      return 2015; // œ
      case SDLK_COMMA:  return 2012; // ç
      case SDLK_5:      return 2013; // €

      case SDLK_6:            _circumflex = true; return 0;
      case SDLK_BACKQUOTE:    _grave = true; return 0;
    }
  }

  return 0;
}

// ----------------------------------------------------------------------------------------------------
// AZERTY ---------------------------------------------------------------------------------------------
/*
 * Convert the current SDL keycode event to the Kebb keycode for the French version.
 * Return the keycode or 0 (0 is not count as a fail by WindowGame).
 * It uses these keycodes:
 *      https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_french.h
 */
uint16_t Controller::convert_fr(SDL_Event &e) {

  const auto mask = 0x3FF; // Remove the first sixth bits (NUM/CAP/GUI)
                           // std::cout << "mode: " << (e.key.keysym.mod & mask) << std::endl;

  // clang-format off
  // --------------------------------------------------
  // French specials ----------------------------------
  if (_circumflex) {
    _circumflex = false;
    if ((e.key.keysym.mod & KMOD_CAPS) == KMOD_CAPS) {
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
  } else if (_diaeresis) {
    _diaeresis = false;

    if ((e.key.keysym.mod & KMOD_CAPS) == KMOD_CAPS) {
      switch (e.key.keysym.sym) {
        case SDLK_i:       return 2109; // Ï
        case SDLK_e:       return 2110; // Ë
        case SDLK_u:       return 2111; // Ü
      }
    } else {
      switch (e.key.keysym.sym) {
        case SDLK_i:       return 2009; // ï
        case SDLK_e:       return 2010; // ë
        case SDLK_u:       return 2011; // ü
      }
    }
  }

  if ((e.key.keysym.mod & KMOD_CAPS & KMOD_SHIFT) == (KMOD_CAPS & KMOD_SHIFT)){
      switch (e.key.keysym.sym) {
        case 50:       return 2100; // É
        case 57:       return 2112; // Ç
        case 48:       return 2101; // À
        case 55:       return 2102; // È
        case 249:      return 2103; // Ù
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

      case SDLK_KP_0:    return 500;
      case SDLK_KP_1:    return 501;
      case SDLK_KP_2:    return 502;
      case SDLK_KP_3:    return 503;
      case SDLK_KP_4:    return 504;
      case SDLK_KP_5:    return 505;
      case SDLK_KP_6:    return 506;
      case SDLK_KP_7:    return 507;
      case SDLK_KP_8:    return 508;
      case SDLK_KP_9:    return 509;

      case 49:           return 1005; // &
      case 50:           return 2000; // é
      case 51:           return 1006; // "
      case 52:           return 1001; // '
      case 53:           return 1007; // (
      case 54:           return 1013; // -
      case 55:           return 2002; // è
      case 56:           return 1027; // _
      case 57:           return 2012; // ç
      case 48:           return 2001; // à
      case 41:           return 1008; // )
      case 61:           return 1019; // =

      case 1073741824:            _circumflex = true; return 0;
      case 36:           return 1004; // $
      case 249:          return 2003; // ù
      case 42:           return 1010; // *

      case 33:           return 1000; // !
      case 58:           return 1016; // :
      case 59:           return 1017; // ;
      case 44:           return 1012; // ,

      case 60:           return 1018; // <
    }
  }

  if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {

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

      case 49:           return 501; // 1
      case 50:           return 502; // 2
      case 51:           return 503; // 3
      case 52:           return 504; // 4
      case 53:           return 505; // 5
      case 54:           return 506; // 6
      case 55:           return 507; // 7
      case 56:           return 508; // 8
      case 57:           return 509; // 9
      case 48:           return 500; // 0
      // case 41:           return ; // ° (ignored)
      case 61:           return 1019; // =

      case 1073741824:            _diaeresis = true; return 0; // Strange but right
      // case 36:           return ; // £ (ignored)
      case 249:          return 1003; // %
      // case 42:           return ; // µ (ignored)

      // case 33:           return ; // § (ignored)
      case 58:           return 1015; // /
      case 59:           return 1014; // .
      case 44:           return 1021; // ?

      case 60:           return 1020; // >
    }
  }

  if ((e.key.keysym.mod & KMOD_RALT) == KMOD_RALT) {
    switch (e.key.keysym.sym) {

      case 50:           return 1028; // ~
      case 51:           return 1002; // #
      case 52:           return 1029; // {
      case 53:           return 1023; // [
      case 54:           return 1031; // |
      case 55:           return 1009; // `
      case 56:           return 1024; // Backslash
      case 57:           return 1026; // ^
      case 48:           return 1022; // @
      case 41:           return 1025; // ]
      case 61:           return 1030; // }
      case SDLK_e:       return 2015; // €
    }
  }

  return 0;
}

// ----------------------------------------------------------------------------------------------------
// BEPO -----------------------------------------------------------------------------------------------
/*
 * Convert the current SDL keycode event to the Kebb keycode for the French bépo version.
 * Return the keycode or 0 (0 is not count as a fail by WindowGame).
 * It uses these keycodes:
 *      https://github.com/qmk/qmk_firmware/blob/master/quantum/keymap_extras/keymap_bepo.h
 */
uint16_t Controller::convert_bepo(SDL_Event &e) {

  const auto mask = 0x3FF; // Remove the first sixth bits (NUM/CAP/GUI)
                           // std::cout << "mode: " << (e.key.keysym.mod & mask) << std::endl;

  // clang-format off
  std::cout << "BÉPO" << std::endl;
  std::cout << "mode: " << e.key.keysym.mod << std::endl;
  std::cout << "keysym: " << e.key.keysym.sym << std::endl;

  if ((e.key.keysym.mod & KMOD_LCTRL) == KMOD_LCTRL && (e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT) {

    std::cout << "control is pressed ! and shift !!!" << std::endl;





  }

  // --------------------------------------------------
  // French specials ----------------------------------
  if (_circumflex) {
    _circumflex = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case 97:        return 2104; // Â
        case 101:       return 2105; // Ê
        case 105:       return 2106; // Î
        case 111:       return 2107; // Ô
        case 117:       return 2108; // Û
      }
    } else {
      switch (e.key.keysym.sym) {
        case 97:        return 2004; // â
        case 101:       return 2005; // ê
        case 105:       return 2006; // î
        case 111:       return 2007; // ô
        case 117:       return 2008; // û
      }
    }
  } else if (_grave) {
    _grave = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case 97:        return 2101; // À
        case 101:       return 2102; // È
        case 117:       return 2103; // Ù
      }
    } else {
      switch (e.key.keysym.sym) {
        case 97:        return 2001; // à
        case 101:       return 2002; // è
        case 117:       return 2003; // ù
      }
    }
  } else if (_diaeresis) {
    _diaeresis = false;

    if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {
      switch (e.key.keysym.sym) {
        case 105:       return 2109; // Ï
        case 101:       return 2110; // Ë
        case 117:       return 2111; // Ü
      }
    } else {
      switch (e.key.keysym.sym) {
        case 105:       return 2009; // ï
        case 101:       return 2010; // ë
        case 117:       return 2011; // ü
      }
    }
  }

  if ((e.key.keysym.mod & KMOD_RALT) == KMOD_RALT && (
  (e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT)) {
    switch (e.key.keysym.sym) {
      case 97:       return 2113; // Æ
      case 111:      return 2114; // Œ
      case 117:      return 2103; // Ù
    }
  }

  // --------------------------------------------------
  // --------------------------------------------------
  if ((e.key.keysym.mod & _mask_mod) == KMOD_NONE) {
    switch (e.key.keysym.sym) {
      case 97:       return 10; // a
      case 98:       return 11; // b
      case 99:       return 12; // c
      case 100:      return 13; // d
      case 101:      return 14; // e
      case 102:      return 15; // f
      case 103:      return 16; // g
      case 104:      return 17; // h
      case 105:      return 18; // i
      case 106:      return 19; // j
      case 107:      return 20; // k
      case 108:      return 21; // l
      case 109:      return 22; // m
      case 110:      return 23; // n
      case 111:      return 24; // o
      case 112:      return 25; // p
      case 113:      return 26; // q
      case 114:      return 27; // r
      case 115:      return 28; // s
      case 116:      return 29; // t
      case 117:      return 30; // u
      case 118:      return 31; // v
      case 119:      return 32; // w
      case 120:      return 33; // x
      case 121:      return 34; // y
      case 122:      return 35; // z

      case 233:      return 2000; // é
      case 232:      return 2002; // è
      case 231:      return 2012; // ç
      case 224:      return 2001; // à

      case SDLK_KP_0:    return 500;
      case SDLK_KP_1:    return 501;
      case SDLK_KP_2:    return 502;
      case SDLK_KP_3:    return 503;
      case SDLK_KP_4:    return 504;
      case SDLK_KP_5:    return 505;
      case SDLK_KP_6:    return 506;
      case SDLK_KP_7:    return 507;
      case SDLK_KP_8:    return 508;
      case SDLK_KP_9:    return 509;

      case 36:           return 1004; // $
      case 49:           return 1006; // "
      // case 50:           return ; // «
      // case 51:           return ; // »
      case 52:           return 1007; // (
      case 53:           return 1008; // )
      case 54:           return 1022; // @
      case 55:           return 1011; // +
      case 56:           return 1013; // -
      case 57:           return 1015; // /
      case 48:           return 1010; // *
      case 61:           return 1019; // =
      case 37:           return 1003; // %

      case 1073741824:            _circumflex = true; return 0;
      case 44:           return 1012; // ,
      case 46:           return 1014; // .
      case 39:           return 1001; // '
    }
  }

  if ((e.key.keysym.mod & KMOD_LSHIFT) == KMOD_LSHIFT || (e.key.keysym.mod & KMOD_RSHIFT) == KMOD_RSHIFT) {

    switch (e.key.keysym.sym) {
      case 97:       return 100; // A
      case 98:       return 101; // B
      case 99:       return 102; // C
      case 100:      return 103; // D
      case 101:      return 104; // E
      case 102:      return 105; // F
      case 103:      return 106; // G
      case 104:      return 107; // H
      case 105:      return 108; // I
      case 106:      return 109; // J
      case 107:      return 110; // K
      case 108:      return 111; // L
      case 109:      return 112; // M
      case 110:      return 113; // N
      case 111:      return 114; // O
      case 112:      return 115; // P
      case 113:      return 116; // Q
      case 114:      return 117; // R
      case 115:      return 118; // S
      case 116:      return 119; // T
      case 117:      return 120; // U
      case 118:      return 121; // V
      case 119:      return 122; // W
      case 120:      return 123; // X
      case 121:      return 124; // Y
      case 122:      return 125; // Z

      case 233:      return 2100; // É
      case 232:      return 2102; // È
      case 231:      return 2112; // Ç
      case 224:      return 2101; // À

      case 36:           return 1002; // #
      case 49:           return 501; // 1
      case 50:           return 502; // 2
      case 51:           return 503; // 3
      case 52:           return 504; // 4
      case 53:           return 505; // 5
      case 54:           return 506; // 6
      case 55:           return 507; // 7
      case 56:           return 508; // 8
      case 57:           return 509; // 9
      case 48:           return 500; // 0
      // case 61:           return ; // °
      case 37:           return 1009; // `

      case 1073741824:   return 1000; // !
      case 44:           return 1017; // ;
      case 46:           return 1016; // :
      case 39:           return 1021; // ?
    }
  }

  if ((e.key.keysym.mod & KMOD_RALT) == KMOD_RALT) {
    switch (e.key.keysym.sym) {

      // case 36:           return ; // –
      // case 49:           return ; // —
      case 50:           return 502; // <
      case 51:           return 503; // >
      case 52:           return 504; // [
      case 53:           return 505; // ]
      case 54:           return 506; // ^
      // case 55:           return ; // ±
      // case 56:           return ; // −
      // case 57:           return ; // ÷
      // case 48:           return ; // ×
      // case 61:           return ; // ≠
      // case 37:           return ; // ‰

      case 32:           return 1027; // _

      case 97:       return 2014; // æ
      case 98:       return 1031; // |
      case 101:      return 2013; // €
      case 105:             _diaeresis = true; return 0;
      case 107:      return 1028; // ~
      case 111:      return 2015; // œ
      case 112:      return 1005; // &
      case 117:      return 2003; // ù
      case 120:      return 1029; // }
      case 121:      return 1030; // {

      case 232:             _grave = true; return 0;
      case 224:      return 1024; // Backslash
    }
  }

  return 0;
}
