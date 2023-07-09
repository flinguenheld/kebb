#include "score.h"

Score::Score(uint16_t screen_width, boxsize char_size) : _sucess(0), _fail(0), _miss(0) {

  // Geometry
  // Success, fail and miss on the right --
  boxsize bs = {static_cast<uint16_t>(char_size.w * 12), static_cast<uint16_t>(char_size.h)};
  point pt = {static_cast<uint16_t>(screen_width - bs.w - char_size.h * 0.1),
              static_cast<uint16_t>(char_size.h * 0.1)};

  _textbox_success = std::make_unique<WidgetTextBox>(pt, bs);
  pt.y += char_size.h;
  _textbox_fail = std::make_unique<WidgetTextBox>(pt, bs);
  pt.y += char_size.h;
  _textbox_miss = std::make_unique<WidgetTextBox>(pt, bs);

  // Timer bigger and on the left --
  bs.w = char_size.w * 1.5 * 5;
  bs.h = char_size.h * 1.5;

  pt.x = char_size.h * 1.5 * 0.2;
  pt.y = char_size.h * 1.5 * 0.2;
  _textbox_time = std::make_unique<WidgetTextBox>(pt, bs);

  // Colors : Catpuccin Latte
  _textbox_time->set_color_text({137, 180, 250, 200});  // Blue
  _textbox_success->set_color_text({64, 160, 43, 150}); // Green
  _textbox_fail->set_color_text({254, 100, 11, 150});   // Peach
  _textbox_miss->set_color_text({230, 69, 83, 150});    // Maroon

  // TODO: Start the timer when the game is launch
  start_timer();
}

void Score::start_timer() { _timer_start = std::chrono::steady_clock().now(); }

std::string Score::int_to_string(uint16_t i, uint8_t text_length, char c) {
  std::string text = std::to_string(i);
  while (text.length() < text_length)
    text.insert(0, 1, c);

  return text;
}

void Score::render(SDL_Renderer *renderer, TTF_Font *font) {

  std::unique_lock<std::mutex> ul(_mutex);
  _textbox_success->set_text("Success: " + int_to_string(_sucess, 4));
  _textbox_fail->set_text("Fail: " + int_to_string(_fail, 6));
  _textbox_miss->set_text("Miss: " + int_to_string(_miss, 6));
  ul.unlock();

  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock().now() - _timer_start)
          .count();

  _textbox_time->set_text(int_to_string(duration / 60, 2, '0') + ":" + int_to_string(duration % 60, 2, '0'));

  _textbox_time->render(renderer, font);
  _textbox_success->render(renderer, font);
  _textbox_fail->render(renderer, font);
  _textbox_miss->render(renderer, font);
}

void Score::up_sucess() {
  std::unique_lock<std::mutex> ul(_mutex);
  _sucess++;
}
void Score::up_fail() {
  std::unique_lock<std::mutex> ul(_mutex);
  _fail++;
}
void Score::up_miss() {
  std::unique_lock<std::mutex> ul(_mutex);
  _miss++;
}
