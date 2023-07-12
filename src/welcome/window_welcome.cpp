#include "window_welcome.h"
#include "welcome/widget_logo.h"
#include <memory>

WindowWelcome::WindowWelcome(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                             std::shared_ptr<Renderer> renderer)
    : WidgetWindow(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Valid");

  // Geometry
  boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  boxsize line_size;
  point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(5);
  line_size.w = char_size.w * 4;
  line_size.h = char_size.h;

  pt.x = screen_size.w / 2 - line_size.w / 2;
  pt.y = line_size.h * 0.2;

  _widget_title = std::make_unique<WidgetTextBox>(pt, line_size);
  _widget_title->set_text("Kebb");

  // Catppuccin: Mocha
  _widget_title->set_color_text({250, 179, 135, 200}); // Peach
  // _widget_title->set_color_text({242, 205, 205, 200}); // Flamingo
  // _widget_title->set_color_text({180, 190, 254, 200}); // Lavender
  // _textbox_time->set_color_text({148, 226, 213, 200}); // Teal

  // ------------------------------------------------------------------------
  // Logo -------------------------------------------------------------------
  boxsize bs = {static_cast<uint16_t>(screen_size.w / 3), static_cast<uint16_t>(screen_size.w / 7)};
  pt.x = screen_size.w / 2 - bs.w / 2;
  pt.y = screen_size.h / 3;

  _widget_logo = std::make_unique<WidgetLogo>(pt, bs);
}

WindowWelcome::~WindowWelcome() {}

void WindowWelcome::render() {

  _widget_logo->update();

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_logo->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcome::control_escape() { *_next_window = WindowName::W_Quit; }
void WindowWelcome::control_enter() {
  *_next_window = WindowName::W_Game;
} // TODO: Change according to selection
