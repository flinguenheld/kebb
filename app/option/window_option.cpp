#include "window_option.h"

WindowOption::WindowOption(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                           std::shared_ptr<Renderer> renderer, std::shared_ptr<OptionFile> options,
                           std::shared_ptr<LayoutFile> layouts)
    : WidgetWindowSelection(next_window_id, renderer), _options(options), _layouts(layouts),
      _message_displayed(false), _screen_size(screen_size) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Cancel     <ENTER> Save");

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Options",
                                                  widget::color(widget::ColorName::C_Peach));

  pt.y += char_size.h;

  // ------------------------------------------------------------------------
  // Selection fields -------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.1);
  const uint16_t y_long_space = char_size.h * 2;
  const uint16_t y_medium_space = char_size.h * 1.5;
  const uint16_t y_small_space = char_size.h * 1.03;

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetList>(pt, char_size, "Resolution:",
                                   // std::vector<SelectionItem>{{"480x480", "480-25"}, // Logic: ~12 000
                                   //                            {"640x640", "640-19"},
                                   //                            {"800x800", "800-15"},
                                   //                            {"1024x1024", "1024-12"}},

                                   std::vector<SelectionItem>{{"480x480", "480-20"}, // Logic: ~9 600
                                                              {"640x640", "640-15"},
                                                              {"800x800", "800-12"},
                                                              {"1024x1024", "1024-9"}},
                                   true));
  _widget_select_fields.back()->set_choice_by_value(_options->get().resolution);

  pt.y += y_small_space;
  std::vector<SelectionItem> list_layouts;
  for (const auto &l : _layouts->list_layouts())
    list_layouts.emplace_back(SelectionItem{.text = l, .value_string = l});

  _widget_select_fields.emplace_back(
      std::make_unique<WidgetList>(pt, char_size, "Keyboard layout:", std::move(list_layouts)));
  _widget_select_fields.back()->set_choice_by_value(_options->get().layout);

  pt.y += y_medium_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Letters"));
  _widget_select_fields.back()->set_bool(_options->get().letters);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Capitals"));
  _widget_select_fields.back()->set_bool(_options->get().capitals);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Numbers"));
  _widget_select_fields.back()->set_bool(_options->get().numbers);

  pt.y += y_medium_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Symbols"));
  _widget_select_fields.back()->set_bool(_options->get().symbols);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Symbols plus"));
  _widget_select_fields.back()->set_bool(_options->get().symbols_plus);

  pt.y += y_medium_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Extras"));
  _widget_select_fields.back()->set_bool(_options->get().extras);

  pt.y += y_small_space;
  _widget_select_fields.emplace_back(std::make_unique<WidgetBoolean>(pt, char_size, "Extra caps"));
  _widget_select_fields.back()->set_bool(_options->get().extra_caps);

  // ------------------------------------------------------------------------
  // Message ----------------------------------------------------------------
  pt.y += y_long_space;
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(0.8);
  _widget_message = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center);
  _widget_message->set_color_text(widget::color(widget::ColorName::C_Base));
  _widget_message->set_color(widget::color(widget::ColorName::C_Yellow));

  // Display help on start --
  check_qwerty_extra();
}

WindowOption::~WindowOption() {}

// ----------------------------------------------------------------------------------------------------
// LOGIC ----------------------------------------------------------------------------------------------
void WindowOption::logic() {

  // Check the layout value
  _widget_select_fields[2]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Letter));
  _widget_select_fields[3]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Letter_cap));
  _widget_select_fields[4]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Number));
  _widget_select_fields[5]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Symbol));
  _widget_select_fields[6]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Symbol_plus));
  _widget_select_fields[7]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Extra));
  _widget_select_fields[8]->set_visible(
      _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Extra_cap));
}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
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
void WindowOption::check_new_resolution() {

  if (_options->get().resolution != _widget_select_fields[0]->get_choice().value_string) {
    _widget_message->move_text("  Restart the application to set the new resolution.  ");
    _message_displayed = true;
  }
}
void WindowOption::check_qwerty_extra() {

  if ((_widget_select_fields[6]->get_bool() || _widget_select_fields[7]->get_bool()) &&
      _widget_select_fields[1]->get_choice().value_string == "qwerty") {
    _widget_message->move_text("  Extras requier the US Altgr-intl layout  ");
    _message_displayed = true;
  }
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowOption::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
void WindowOption::control_enter() {
  // Use has to select at least one target type
  if ((_widget_select_fields[2]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Letter)) ||
      (_widget_select_fields[3]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Letter_cap)) ||
      (_widget_select_fields[4]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Number)) ||
      (_widget_select_fields[5]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Symbol)) ||
      (_widget_select_fields[6]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Symbol_plus)) ||
      (_widget_select_fields[7]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Extra)) ||
      (_widget_select_fields[8]->get_bool() == true &&
       _layouts->are_there(_widget_select_fields[1]->get_choice().value_string, TypeChar::Extra_cap))) {

    // Update the layout ?
    if (_widget_select_fields[1]->get_choice().value_string != _options->get().layout)
      _layouts->set_layout(_widget_select_fields[1]->get_choice().value_string);

    // Up options, save and quit
    _options->set().resolution = _widget_select_fields[0]->get_choice().value_string;
    _options->set().layout = _widget_select_fields[1]->get_choice().value_string;
    _options->set().letters = _widget_select_fields[2]->get_bool();
    _options->set().capitals = _widget_select_fields[3]->get_bool();
    _options->set().numbers = _widget_select_fields[4]->get_bool();
    _options->set().symbols = _widget_select_fields[5]->get_bool();
    _options->set().symbols_plus = _widget_select_fields[6]->get_bool();
    _options->set().extras = _widget_select_fields[7]->get_bool();
    _options->set().extra_caps = _widget_select_fields[8]->get_bool();

    *_next_window_id = uint8_t(kebb::WindowName::W_Welcome);
  } else
    _widget_message->move_text("  At least one target type is requiered.  ");
}

void WindowOption::control_left() {

  _message_displayed = false;
  for (auto &w : _widget_select_fields) {
    if (w->is_selected()) {
      w->action_left();

      check_qwerty_extra();
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

      check_qwerty_extra();
      check_new_resolution();
      return;
    }
  }
}
