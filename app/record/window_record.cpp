#include "window_record.h"

WindowRecord::WindowRecord(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
                           std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records)
    : WidgetWindow(next_window_id, renderer), _records(records) {

  _widget_menu = std::make_unique<WidgetBottomMenu>(screen_size, renderer, "<ESC> Quit");

  // Geometry
  widget::boxsize char_size = _renderer->font_char_size(FontName::F_Menu);
  widget::point pt;

  // ------------------------------------------------------------------------
  // Title ------------------------------------------------------------------
  char_size.set_scale(3);
  pt.x = screen_size.w / 2;
  pt.y = char_size.h * 0.5;

  _widget_title = std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Records",
                                                  widget::color(widget::ColorName::C_Peach));

  pt.y += char_size.h * 0.5;

  // ------------------------------------------------------------------------
  // Text -------------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(1.1);

  _widget_title2 =
      std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center, "Last fifteen games",
                                      widget::color(widget::ColorName::C_Peach));

  pt.y += char_size.h * 1.4;

  // ------------------------------------------------------------------------
  // Entries ----------------------------------------------------------------
  char_size = _renderer->font_char_size(FontName::F_Menu).scale(0.73);

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
      text += "Survival: ";

      switch (e.survival_difficulty) {
      case uint16_t(kebb::SurvivalDifficulty::D_VeryEasy):
        text += "VEasy";
        break;
      case uint16_t(kebb::SurvivalDifficulty::D_Easy):
        text += "Easy";
        break;
      case uint16_t(kebb::SurvivalDifficulty::D_Normal):
        text += "Norm";
        break;
      case uint16_t(kebb::SurvivalDifficulty::D_Hard):
        text += "Hard";
        break;
      case uint16_t(kebb::SurvivalDifficulty::D_VeryHard):
        text += "VHard";
        break;
      default: // Impossible
        text += "Imp";
      }

      text += " " + std::to_string(e.survival_nb_targets) + "/" + std::to_string(e.survival_speed);
      text += " lvl " + std::to_string(e.survival_level_reached);

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
    text += widget::adapt_string_length(std::to_string(e.time_game / 60), 2, '0') + ":" +
            widget::adapt_string_length(std::to_string(e.time_game % 60), 2, '0');

    // Text - scores
    text += " S" + std::to_string(e.success);
    text += " F" + std::to_string(e.fail);
    text += " M" + std::to_string(e.miss);

    // Up size & position
    _entries.emplace_back(std::make_unique<WidgetTextBox>(pt, char_size, TextBoxAlign::TB_Center));
    _entries.back()->move_text(std::move(text));

    if ((kebb::GameMode)e.mode == kebb::GameMode::M_Survival)
      _entries.back()->set_color_text(widget::color(widget::ColorName::C_Text));
    else
      _entries.back()->set_color_text(widget::color(widget::ColorName::C_Sky));

    pt.y += char_size.h * 1.2;
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
void WindowRecord::control_escape() { *_next_window_id = uint8_t(kebb::WindowName::W_Welcome); }
