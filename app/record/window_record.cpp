#include "window_record.h"

WindowRecord::WindowRecord(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
                           std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records)
    : WidgetWindow(next_window, renderer), _records(records) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit");

  // Geometry
  kebb::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  kebb::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Records",
                                                  kebb::color(kebb::ColorName::C_Peach));

  pt.y += char_size.h * 0.5;

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.1);

  _widget_title2 = std::make_unique<WidgetTextBox>(
      pt, char_size, TextBoxAlign::TB_Center, "Last fifteen games", kebb::color(kebb::ColorName::C_Peach));

  pt.y += char_size.h * 1.4;

  // ------------------------------------------------------------------------
  // Entries ----------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(0.75);

  for (const auto &e : _records->records()) {
    std::string text;

    // Date
    struct tm *timeinfo;
    char buffer[9];

    timeinfo = localtime(&e.time_start);
    strftime(buffer, 9, "%y/%m/%d", timeinfo);
    text += buffer;
    text += " ";

    // Text - mode & difficulty
    if ((kebb::GameMode)e.mode == kebb::GameMode::M_Survival) {
      text += "Survival: " + std::to_string(e.survival_nb_targets) + "/" + std::to_string(e.survival_speed);
      text += " lvl " + std::to_string(e.survival_level);

    } else
      text += "Timer: " + std::to_string(e.timer_nb_target) + "/" + std::to_string(e.timer_speed);

    // Text - status
    switch ((kebb::GameStatus)e.status) {
    case kebb::GameStatus::S_Win:
      text += " WON ";
      break;
    case kebb::GameStatus::S_Loose:
      text += " LOST  ";
      break;
    case kebb::GameStatus::S_TimeUp:
      text += " TIMEUP ";
      break;
    default:
      text += " QUIT ";
      break;
    }

    // Time
    text += kebb::adapt_string_length(std::to_string(e.time_game / 60), 2, '0') + ":" +
            kebb::adapt_string_length(std::to_string(e.time_game % 60), 2, '0');

    // Text - scores
    text += " S" + std::to_string(e.success);
    text += " F" + std::to_string(e.fail);
    text += " M" + std::to_string(e.miss);

    // Up size & position
    _entries.emplace_back(std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center));
    _entries.back()->move_text(std::move(text));

    if ((kebb::GameMode)e.mode == kebb::GameMode::M_Survival)
      _entries.back()->set_color_text(kebb::color(kebb::ColorName::C_Text));
    else
      _entries.back()->set_color_text(kebb::color(kebb::ColorName::C_Sky));

    pt.y += char_size.h * 1.15;
  }
}

WindowRecord::~WindowRecord() {}

// ----------------------------------------------------------------------------------------------------
// RENDER ---------------------------------------------------------------------------------------------
void WindowRecord::render() const {

  _renderer->clear_screen();

  _widget_title->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  _widget_title2->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));

  for (const auto &e : _entries) {
    e->render(_renderer->renderer(), _renderer->font(FontName::F_Menu));
  }

  _widget_menu->render();

  // Update Screen
  SDL_RenderPresent(_renderer->renderer());
}

// ----------------------------------------------------------------------------------------------------
// CONTROLS -------------------------------------------------------------------------------------------
void WindowRecord::control_escape() { *_next_window = kebb::WindowName::W_Welcome; }
