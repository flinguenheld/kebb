set(EXE_SOURCES main.cpp
                controller.cpp
                loop.cpp
                renderer.cpp)

add_subdirectory(about)
add_subdirectory(game)
add_subdirectory(option)
add_subdirectory(record)
add_subdirectory(welcome)

add_executable(${PROJECT_NAME} ${EXE_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
                      ${LIBRARY_WIDGET}
                      ${LIBRARY_FILE}
                      SDL2
                      SDL2_ttf)

target_include_directories(${PROJECT_NAME} PUBLIC
  ${CMAKE_BINARY_DIR}/configured_files/include
)
