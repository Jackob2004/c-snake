#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void) {
    initscr();

    printw("Hello World!");
    refresh();
    getch();

    endwin();
    return EXIT_SUCCESS;
}
