cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME kebb)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)


include(FetchContent)

message("Fetch sdl ----------")
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY  https://github.com/libsdl-org/SDL
    # GIT_TAG         release-2.26.3
    GIT_TAG         release-2.0.22
    GIT_PROGRESS    TRUE
)
FetchContent_MakeAvailable(SDL2)

message("Fetch sdl ttf ------")
FetchContent_Declare(
  SDL2_ttf
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf
    GIT_TAG release-2.20.2
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(SDL2_ttf)




set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# Options
option(RELEASE_LINUX "Use the final paths" OFF)
option(DEBUG "Print dev information" OFF)

if (RELEASE_LINUX)
  add_definitions(-DRELEASE_LINUX)
endif()
if (DEBUG)
  add_definitions(-DDEBUG)
endif()


include_directories(src)
add_executable(${PROJECT_NAME} src/main.cpp

                               src/file/layout_file.cpp

                               src/controller.cpp
                               src/loop.cpp
                               src/utils.cpp
                               src/renderer.cpp
                               src/about/window_about.cpp
                               src/file/file.cpp
                               src/file/option_file.cpp
                               src/file/record_file.cpp
                               src/game/target.cpp
                               src/game/dispatcher.cpp
                               src/game/score.cpp
                               src/game/window/window_game.cpp
                               src/game/window/window_gameover.cpp
                               src/game/window/widget_score.cpp
                               src/game/window/survival_mode/widget_gauge.cpp
                               src/game/window/survival_mode/window_survival_mode.cpp
                               src/game/window/survival_mode/window_welcome_survival.cpp
                               src/game/window/timer_mode/window_timer_mode.cpp
                               src/game/window/timer_mode/window_welcome_timer.cpp
                               src/option/window_option.cpp
                               src/record/window_record.cpp
                               src/welcome/widget_logo.cpp
                               src/welcome/window_welcome.cpp
                               src/widget/button/widget_selection.cpp
                               src/widget/button/widget_boolean.cpp
                               src/widget/button/widget_list.cpp
                               src/widget/widget_base.cpp
                               src/widget/widget_textbox.cpp
                               src/widget/window/widget_bottom_menu.cpp
                               src/widget/window/widget_window.cpp)

find_package(Threads)
target_link_libraries(${PROJECT_NAME} Threads::Threads)


target_link_libraries(
  ${PROJECT_NAME}
    SDL2
    SDL2_ttf
)

# Copy files
file(COPY font DESTINATION ${CMAKE_BINARY_DIR})
file(COPY layout DESTINATION ${CMAKE_BINARY_DIR})
