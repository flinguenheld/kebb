#include "widget_list.h"
#include <cstdint>
#include <vector>

WidgetList::WidgetList(point pos_center, boxsize size_char, std::string &&text,
                       std::vector<std::string> &&choices, uint16_t choice_index, bool selected)
    : WidgetSelection(pos_center, size_char, std::move(text), selected), _choices(std::move(choices)) {}

WidgetList::~WidgetList() {}

// ------------------------------------------------------------------------
// Actions ----------------------------------------------------------------
std::string WidgetList::current_selection() const { return "heps"; } // TODO: add return
void WidgetList::set_selection() {}

void WidgetList::action_left() {}
void WidgetList::action_right() {}
