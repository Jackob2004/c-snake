#ifndef SNAKE_SCOREBOARD_H
#define SNAKE_SCOREBOARD_H
#include <ncurses.h>

#include "player.h"
#include "main-menu.h"
#include "menu.h"

#define PAGE_SIZE 5

typedef struct Scoreboard {
    char *title;
    WINDOW *win;
    strings_t *rows;
    int current_page;
    int total_pages;
    bool opened;
    point_t curr_page_info;
} scoreboard_t;

void open_scoreboard(void *ptr);

#endif //SNAKE_SCOREBOARD_H