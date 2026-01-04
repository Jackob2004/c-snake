#include "scoreboard.h"

scoreboard_t *create_scoreboard() {
    scoreboard_t *scoreboard = malloc(sizeof(scoreboard_t));
    scoreboard->title = "Scoreboard";
    scoreboard->rows = get_sorted_players();

    const int COLUMNS = 15 + MAX_NAME_LENGTH;
    const int ROWS = PAGE_SIZE + 4;
    const point_t center = calc_middle_position(COLUMNS, ROWS, stdscr);
    scoreboard->win = newwin(ROWS, COLUMNS, center.y, center.x);
    box(scoreboard->win, '*', 0);

    scoreboard->current_page = 0;
    const bool has_reminder = (int)scoreboard->rows->length % PAGE_SIZE > 0;
    scoreboard->total_pages = (int)scoreboard->rows->length / PAGE_SIZE;
    scoreboard->total_pages = has_reminder ? scoreboard->total_pages + 1: scoreboard->total_pages;

    scoreboard->opened = true;

    scoreboard->curr_page_info.x = 0;
    scoreboard->curr_page_info.y = PAGE_SIZE + 3;

    return scoreboard;
}

void destroy_scoreboard(scoreboard_t *scoreboard) {
    delwin(scoreboard->win);
    destroy_strings(scoreboard->rows);
    free(scoreboard);
}


void display_current_page(void *ptr) {
    scoreboard_t *scoreboard = (scoreboard_t *)ptr;
    wclear(scoreboard->win);
    box(scoreboard->win, '*', 0);

    char *curr_page_str = int_to_str(scoreboard->current_page + 1, 10);
    mvwprintw(scoreboard->win, 0, 1, "%s pages: %d", scoreboard->title, scoreboard->total_pages);
    mvwprintw(scoreboard->win, scoreboard->curr_page_info.y, scoreboard->curr_page_info.x, "Current page: %s", curr_page_str);

    const int start = scoreboard->current_page * PAGE_SIZE;
    int end = start + PAGE_SIZE;
    end = (end > scoreboard->rows->length) ? (int)scoreboard->rows->length : end;

    int count = 1;
    for (int i = start; i < end; i++) {
        mvwprintw(scoreboard->win, count + 1, 3, "%d. %s", i + 1, scoreboard->rows->items[i]);
        count++;
    }

    wrefresh(scoreboard->win);
    free(curr_page_str);
}

void next_page(void *ptr) {
    scoreboard_t *scoreboard = (scoreboard_t *)ptr;
    if (scoreboard->current_page + 1 >= scoreboard->total_pages) return;
    scoreboard->current_page++;
}

void prev_page(void *ptr) {
    scoreboard_t *scoreboard = (scoreboard_t *)ptr;
    if (scoreboard->current_page == 0) return;
    scoreboard->current_page--;
}

void close_scoreboard(void *ptr) {
    scoreboard_t *scoreboard = (scoreboard_t *)ptr;
    scoreboard->opened = false;
}

void open_scoreboard(void *ptr) {
    scoreboard_t *scoreboard = create_scoreboard();

    const int COLUMNS = 40;
    point_t point = calc_middle_position(COLUMNS, 5, stdscr);
    point.y = point.y + scoreboard->curr_page_info.y;
    char *options[] = {"Previous", "Next", "Exit"};
    MenuAction actions[] = {prev_page, next_page, close_scoreboard};
    menu_t *menu = create_menu(COLUMNS, point, 3, options, "Test", actions);

    while (scoreboard->opened) {
        display_current_page(scoreboard);
        const MenuAction chosen_action = process_menu_input(menu);
        chosen_action(scoreboard);
    }

    destroy_menu(menu);
    clear();
    refresh();

    destroy_scoreboard(scoreboard);
    main_menu(NULL);
}