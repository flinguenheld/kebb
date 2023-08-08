#ifndef WINDOW_RECORD
#define WINDOW_RECORD

#include "file/record_file.h"
#include "utils.h"
#include "widget/window/widget_bottom_menu.h"
#include "widget/window/widget_window.h"

/*
 * Display entries saved in record file (calculated for 15 entries).
 */
class WindowRecord : public WidgetWindow {
public:
  WindowRecord(kebb::boxsize screen_size, std::shared_ptr<kebb::WindowName> next_window,
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
