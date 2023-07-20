cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(kebb)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Threads)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

add_executable(Kebb src/main.cpp
                    src/controller.cpp
                    src/loop.cpp
                    src/utils.cpp
                    src/renderer.cpp
                    src/about/window_about.cpp
                    src/game/target.cpp
                    src/game/dispatcher.cpp
                    src/game/window_game.cpp
                    src/option/window_option.cpp
                    src/option/option_file.cpp
                    src/pause/window_pause.cpp
                    src/score/score.cpp
                    src/score/widget_score.cpp
                    src/welcome/widget_logo.cpp
                    src/welcome/window_welcome.cpp
                    src/widget/button/widget_selection.cpp
                    src/widget/button/widget_boolean.cpp
                    src/widget/button/widget_list.cpp
                    src/widget/widget_base.cpp
                    src/widget/widget_menu.cpp
                    src/widget/widget_textbox.cpp
                    src/widget/widget_window.cpp)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Kebb ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
