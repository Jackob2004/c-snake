#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "game.h"
#include "main-menu.h"

int main(void) {
    srand(time(NULL));
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    start_color();
    refresh();

    main_menu(NULL);

    getch();

    endwin();
    return EXIT_SUCCESS;
}