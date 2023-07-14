#include "window_option.h"

WindowOption::WindowOption(boxsize screen_size, std::shared_ptr<WindowName> next_window,
                           std::shared_ptr<Renderer> renderer)
    : WidgetWindowSelection(next_window, renderer) {

  _widget_menu = std::make_unique<WidgetMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Save");

  // Geometry
  boxsize char_size = _renderer->font_char_size(FontName::F_Menu); // NOTE: Use font menu ?
  boxsize bs_title;
  point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3);
  bs_title.w = char_size.w * 4;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Options");

  // Catppuccin: Mocha
  _widget_title->set_color_text({250, 179, 135, 200}); // Peach
  // _widget_title->set_color_text({242, 205, 205, 200}); // Flamingo
  // _widget_title->set_color_text({180, 190, 254, 200}); // Lavender
  // _textbox_time->set_color_text({148, 226, 213, 200}); // Teal

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.1);
  pt.x = screen_size.w / 2;
  pt.y += bs_title.h * 1.7;

  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Keyboard layout", true));
  pt.y += bs_field.h * 1.7;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Simultaneous targets"));
  pt.y += bs_field.h * 1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Countdown"));
  pt.y += bs_field.h * 1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Speed"));
  pt.y += bs_field.h * 1.7;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Include letters"));
  pt.y += bs_field.h * 1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Include capitals"));
  pt.y += bs_field.h * 1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Include numbers"));
  pt.y += bs_field.h * 1;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Include symbols"));
}

WindowOption::~WindowOption() {}

void WindowOption::render() {

  // Clear screen
  SDL_SetRenderDrawColor(_renderer->renderer(), 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(_renderer->renderer());

  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowOption::control_escape() { *_next_window = WindowName::W_Welcome; }
void WindowOption::control_enter() {
  // TODO: check and Save
  *_next_window = WindowName::W_Welcome;
}
