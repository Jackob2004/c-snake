#include "main-menu.h"

void scoreboard() {
    printw("Noting there yet...");
}

void bye_message() {
    printw("Bye...");
}

void stop() {
    const int COLUMNS = 50;
    const point_t spawn_point = calc_middle_position(COLUMNS, 4);
    char *options[] = {"Yes", "No"};
    MenuAction actions[] = {bye_message, main_menu};

    menu_t *menu = create_menu(COLUMNS, spawn_point, 2, options, "Are you sure ?", actions);
    const MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action();
}

void main_menu() {
    const int COLUMNS = 80;
    const point_t spawn_point = calc_middle_position(COLUMNS, 5);
    char *options[] = {"Start", "Scoreboard", "Exit"};
    MenuAction actions[] = {start_game_loop, scoreboard, stop};

    menu_t *menu = create_menu(COLUMNS, spawn_point, 3, options, "Main Menu", actions);
    const MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action();
}
