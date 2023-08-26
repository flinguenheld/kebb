cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME kebb)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) # NOTE: To place ./kebb in build/ (confirm)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# set(EXECUTABLE_OUTPUT_PATH ../)

set(LIBRARY_WIDGET widget)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

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

include_directories(app)
add_subdirectory(app)
add_subdirectory(src)

# Options --
option(RELEASE_LINUX "Use the final paths" OFF)
option(DEBUG "Print dev information" OFF)

if (RELEASE_LINUX)
  add_definitions(-DRELEASE_LINUX)
else ()
  file(COPY font DESTINATION ${CMAKE_BINARY_DIR})
  file(COPY layout DESTINATION ${CMAKE_BINARY_DIR})
endif()

if (DEBUG)
  add_definitions(-DDEBUG)
endif()

