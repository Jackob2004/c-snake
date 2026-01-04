#include "main-menu.h"

#include "scoreboard.h"

void scoreboard(void *ptr) {
    open_scoreboard(NULL);
}

void bye_message(void *ptr) {
    printw("Bye...");
}

void stop() {
    const int COLUMNS = 50;
    const point_t spawn_point = calc_middle_position(COLUMNS, 4, stdscr);
    char *options[] = {"Yes", "No"};
    MenuAction actions[] = {bye_message, main_menu};

    menu_t *menu = create_menu(COLUMNS, spawn_point, 2, options, "Are you sure ?", actions);
    const MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action(NULL);
}

void main_menu(void *ptr) {
    const int COLUMNS = 80;
    const point_t spawn_point = calc_middle_position(COLUMNS, 5, stdscr);
    char *options[] = {"Start", "Scoreboard", "Exit"};
    MenuAction actions[] = {start_game_loop, scoreboard, stop};

    menu_t *menu = create_menu(COLUMNS, spawn_point, 3, options, "Main Menu", actions);
    const MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action(NULL);
}
