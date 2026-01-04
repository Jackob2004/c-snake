cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(snake main.c
        menu.c
        menu.h
        snake.c
        snake.h
        game.c
        game.h
        apple.c
        apple.h
        point.h
        main-menu.c
        main-menu.h
        point.c
        player.c
        player.h
        array.h
        scoreboard.c
        scoreboard.h
        string-util.c
        string-util.h
)

target_link_libraries(snake ${CURSES_LIBRARIES})
