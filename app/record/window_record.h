#ifndef WINDOW_RECORD
#define WINDOW_RECORD

#include "file_record.h"
#include "kebb.h"
#include "window/widget_bottom_menu.h"
#include "window/widget_window.h"

/*
 * Display entries saved in record file (calculated for 15 entries).
 */
class WindowRecord : public WidgetWindow {
public:
  WindowRecord(widget::boxsize screen_size, std::shared_ptr<uint8_t> next_window_id,
               std::shared_ptr<Renderer> renderer, std::shared_ptr<RecordFile> records);
  virtual ~WindowRecord() override;

  virtual void control_escape() override;
  virtual void render() const override;

private:
  std::shared_ptr<RecordFile> _records;

  std::unique_ptr<WidgetTextBox> _widget_title;
  std::unique_ptr<WidgetTextBox> _widget_title2;
  std::vector<std::unique_ptr<WidgetTextBox>> _entries;

  std::unique_ptr<WidgetBottomMenu> _widget_menu;
};

#endif // !WINDOW_RECORD
