#include "main-menu.h"

void scoreboard() {
    printw("Noting there yet...");
}

void stop() {
    printw("Bye...");
}

void main_menu() {
    point_t point = {20, 20};
    char *options[] = {"Start", "Scoreboard", "Exit"};
    MenuAction actions[] = {start_game_loop, scoreboard, stop};
    menu_t *menu = create_menu(80, point, 3, options, "Main Menu", actions);
    MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action();
}
