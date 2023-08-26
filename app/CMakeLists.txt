set(EXE_SOURCES main.cpp
                controller.cpp
                loop.cpp
                utils.cpp
                renderer.cpp)

add_subdirectory(about)
add_subdirectory(file)
add_subdirectory(game)
add_subdirectory(option)
add_subdirectory(record)
add_subdirectory(welcome)

message(${PROJECT_NAME})
add_executable(${PROJECT_NAME} ${EXE_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC
                      ${LIBRARY_WIDGET}
                      SDL2
                      SDL2_ttf)
