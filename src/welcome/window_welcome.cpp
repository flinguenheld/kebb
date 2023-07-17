#include "window_welcome.h"

WindowWelcome::WindowWelcome(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                             std::shared_ptr<Renderer> renderer)
    : WidgetWindowSelection(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Quit      <ENTER> Valid");

  // Geometry
  boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  boxsize bs_title;
  point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(5);
  bs_title.w = char_size.w * 4;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Kebb");

  // Catppuccin: Mocha
  _widget_title->set_color_text({250, 179, 135, 200}); // Peach
  // _widget_title->set_color_text({242, 205, 205, 200}); // Flamingo
  // _widget_title->set_color_text({180, 190, 254, 200}); // Lavender
  // _textbox_time->set_color_text({148, 226, 213, 200}); // Teal

  // ------------------------------------------------------------------------
  // Logo -------------------------------------------------------------------
  boxsize bs_logo = {static_cast<uint16_t>(screen_size.w / 3), static_cast<uint16_t>(screen_size.w / 7.5)};
  pt.x = screen_size.w / 2 - bs_logo.w / 2;
  pt.y += bs_title.h * 1.05;

  _widget_logo = std::make_shared<WidgetLogo>(pt, bs_logo);
  _thread = std::thread(&WidgetLogo::update, _widget_logo);

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.7);
  pt.x = screen_size.w / 2;
  pt.y += bs_logo.h * 1.7;

  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, bs_field, "Play", true));
  pt.y += bs_field.h * 1.1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, bs_field, "Options"));
  pt.y += bs_field.h * 1.1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetSelection>(pt, bs_field, "About"));
}

WindowWelcome::~WindowWelcome() {
  _widget_logo->stop();
  _thread.join();
}

void WindowWelcome::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_logo->render(_renderer->renderer());

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowWelcome::control_escape() { *_next_window = WindowName::W_Quit; }
void WindowWelcome::control_enter() {

  if (_widget_select_fields[0]->is_selected())
    *_next_window = WindowName::W_Game;
  else if (_widget_select_fields[1]->is_selected())
    *_next_window = WindowName::W_Option;
  else if (_widget_select_fields[2]->is_selected())
    *_next_window = WindowName::W_About;
}
