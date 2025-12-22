cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(snake main.c
        menu.c
        menu.h)

target_link_libraries(snake ${CURSES_LIBRARIES})
