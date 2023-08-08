#include "window_option.h"

WindowOption::WindowOption(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                           std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options)
    : WidgetWindowSelection(next_window, renderer), _options(options), _message_displayed(false),
      _screen_size(screen_size) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Save");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::boxsize bs_title;
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3);
  bs_title.w = char_size.w * 7;
  bs_title.h = char_size.h;

  pt.x = screen_size.w / 2 - bs_title.w / 2;
  pt.y = bs_title.h * 0.05;

  _widget_title = std::make_unique<WidgetTextBox>(pt, bs_title);
  _widget_title->set_text("Options");
  _widget_title->set_color_text(kebb::color(kebb::ColorName::C_Peach));

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  const kebb::boxsize bs_field = renderer->font_char_size(FontName::F_Menu).scale(1.1);
  const uint16_t y_long_space = bs_field.h * 2;
  const uint16_t y_medium_space = bs_field.h * 1.5;
  const uint16_t y_small_space = bs_field.h * 1.03;

  pt.x = screen_size.w / 2;
  pt.y += bs_title.h * 1.5;

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetList>(pt, bs_field, "Resolution:",
                                   std::vector<SelectionItem>{{"480x480", "480-20"}, // NOTE: Are scales ok ?
                                                              {"640x640", "640-15"},
                                                              {"800x800", "800-10"},
                                                              {"1024x1024", "1024-5"}},
                                   true));
  _widget_select_fields.back()->set_choice_by_value(_options->get().resolution);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetList>(
      pt, bs_field, "Keyboard layout:",
      std::vector<SelectionItem>{{"QWERTY", "US"}, {"AZERTY", "FR"}, {"BEPO (beta)", "BEPO"}}));
  _widget_select_fields.back()->set_choice_by_value(_options->get().layout);

  pt.y += y_long_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Letters"));
  _widget_select_fields.back()->set_bool(_options->get().letters);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Capitals"));
  _widget_select_fields.back()->set_bool(_options->get().capitals);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Numbers"));
  _widget_select_fields.back()->set_bool(_options->get().numbers);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "Symbols"));
  _widget_select_fields.back()->set_bool(_options->get().symbols);

  pt.y += y_medium_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "French extras"));
  _widget_select_fields.back()->set_bool(_options->get().french_extras);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, bs_field, "French extra caps"));
  _widget_select_fields.back()->set_bool(_options->get().french_extra_caps);

  // ------------------------------------------------------------------------
  // Message ----------------------------------------------------------------
  pt.y += y_long_space;
  _widget_message = std::make_unique<WidgetTextBox>(pt, bs_field);
  _widget_message->set_color_text(kebb::color(kebb::ColorName::C_Base));
  _widget_message->set_color(kebb::color(kebb::ColorName::C_Yellow));

  // Display help on start --
  check_french_extra();
}

WindowOption::~WindowOption() {}

void WindowOption::render() const {

  _renderer->clear_screen();
  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (auto &w : _widget_select_fields)
    w->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  _widget_menu->render();

  if (_message_displayed)
    _widget_message->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// MESSAGE --------------------------------------------------------------------------------------------
/*
 * Resize the _Widget_message and set the text.
 */
void WindowOption::display_message(std::string &&message) {

  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  char_size.set_scale(0.8);
  _widget_message->set_w(char_size.w * message.length());
  _widget_message->set_text(std::move(message));

  _widget_message->set_x(_screen_size.w / 2 - _widget_message->size().w / 2);
  _message_displayed = true;
}

void WindowOption::check_new_resolution() {

  if (_options->get().resolution != _widget_select_fields[0]->get_choice().value_string) {
    display_message("  Restart the application to set the new resolution.  ");
    _message_displayed = true;
  }
}
void WindowOption::check_french_extra() {

  if ((_widget_select_fields[6]->get_bool() || _widget_select_fields[7]->get_bool()) &&
      _widget_select_fields[1]->get_choice().value_string == "US") {
    display_message("  French extras requier the US Altgr-intl layout  ");
    _message_displayed = true;
  }
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowOption::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
void WindowOption::control_enter() {
  // Use has to select at least one target type
  if (_widget_select_fields[2]->get_bool() == true || _widget_select_fields[3]->get_bool() == true ||
      _widget_select_fields[4]->get_bool() == true || _widget_select_fields[4]->get_bool() == true ||
      _widget_select_fields[5]->get_bool() == true || _widget_select_fields[6]->get_bool() == true) {

    // Up options, save and quit
    _options->set().resolution = _widget_select_fields[0]->get_choice().value_string;
    _options->set().layout = _widget_select_fields[1]->get_choice().value_string;
    _options->set().letters = _widget_select_fields[2]->get_bool();
    _options->set().capitals = _widget_select_fields[3]->get_bool();
    _options->set().numbers = _widget_select_fields[4]->get_bool();
    _options->set().symbols = _widget_select_fields[5]->get_bool();
    _options->set().french_extras = _widget_select_fields[6]->get_bool();
    _options->set().french_extra_caps = _widget_select_fields[7]->get_bool();

    *_next_window = kebb::WindowName::W_Welcome;
  } else
    display_message("  At least one target type is requiered.  ");
}

void WindowOption::control_left() {

  _message_displayed = false;
  for (auto &w : _widget_select_fields) {
    if (w->is_selected()) {
      w->action_left();

      check_french_extra();
      check_new_resolution();
      return;
    }
  }
}
void WindowOption::control_right() {

  _message_displayed = false;
  for (auto &w : _widget_select_fields) {
    if (w->is_selected()) {
      w->action_right();

      check_french_extra();
      check_new_resolution();
      return;
    }
  }
}
