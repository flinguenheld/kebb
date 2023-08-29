set(LIB_WIDGET_SOURCES
    button/widget_selection.cpp
    button/widget_boolean.cpp
    button/widget_list.cpp
    widget_base.cpp
    widget_textbox.cpp
    window/widget_bottom_menu.cpp
    window/widget_window.cpp)

set(LIB_WIDGET_HEADERS
    button/widget_selection.h
    button/widget_boolean.h
    button/widget_list.h
    widget_base.h
    widget_textbox.h
    window/widget_bottom_menu.h
    window/widget_window.h)

set(LIB_WIDGET_INCLUDES
    ./
    ${CMAKE_BINARY_DIR}/include/${LIBRARY_WIDGET})

add_library(${LIBRARY_WIDGET} STATIC
            ${LIB_WIDGET_SOURCES}
            ${LIB_WIDGET_HEADERS})

target_include_directories(${LIBRARY_WIDGET} PUBLIC
                           ${LIB_WIDGET_INCLUDES})

target_link_libraries(${LIBRARY_WIDGET} PUBLIC
                      SDL2
                      SDL2_ttf)
