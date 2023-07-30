project(kebb)

cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# Options
option(RELEASE_LINUX "Use the final paths" OFF)

if (RELEASE_LINUX)
  add_definitions(-DRELEASE_LINUX)
endif()

# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

include_directories(src)
add_executable(${PROJECT_NAME} src/main.cpp
                               src/controller.cpp
                               src/loop.cpp
                               src/utils.cpp
                               src/renderer.cpp
                               src/about/window_about.cpp
                               src/game/target.cpp
                               src/game/dispatcher.cpp
                               src/game/window/window_game.cpp
                               src/game/window/window_game_timer.cpp
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

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)

find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# Copy fonts
file(COPY font DESTINATION ${CMAKE_BINARY_DIR})
