set(LIB_FILE_SOURCES
    file.cpp
    file_layout.cpp
    file_option.cpp
    file_record.cpp)

  set(LIB_HEADERS
    file.h
    file_layout.h
    file_option.h
    file_record.h)

  set(LIB_FILE_INCLUDES
    ./
    ${CMAKE_BINARY_DIR}/include/${LIBRARY_FILE})

add_library(${LIBRARY_FILE} STATIC
            ${LIB_FILE_SOURCES}
            ${LIB_FILE_HEADERS})

target_include_directories(${LIBRARY_FILE} PUBLIC
                           ${LIB_FILE_INCLUDES})
