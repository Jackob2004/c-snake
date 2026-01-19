#include "menu.h"

void render_menu(const menu_t *menu) {
    for (int i = 0; i < menu->number_of_items; i++) {
        if (i == menu->selected) {
            wattron(menu->window, A_REVERSE);
        }
        mvwprintw(menu->window,i+1, 1, "%s", menu->options[i]);
        wattroff(menu->window, A_REVERSE);
    }
}

menu_t *create_menu(const int columns, const point_t spawn_point, const size_t number_of_items, char **options, char *title, MenuAction *actions) {
    menu_t *menu = (menu_t *)malloc(sizeof(menu_t));
    if (menu == NULL) {
        exit(EXIT_FAILURE);
    }
    menu->number_of_items = number_of_items;
    menu->options = options;
    menu->title = title;
    menu->actions = actions;

    const int OPTION_LENGTH = columns - 2;

    add_trailing_spaces(number_of_items, OPTION_LENGTH, options);

    menu->selected = 0;
    const int rows = (int)menu->number_of_items + 2;
    menu->window = newwin(rows, columns, spawn_point.y, spawn_point.x);
    box(menu->window, '|', 0);

    return menu;
}

MenuAction process_menu_input(menu_t *menu) {
    mvwprintw(menu->window, 0, 0, "%s", menu->title);
    keypad(menu->window, true);

    while (1) {
        render_menu(menu);

        const int input = wgetch(menu->window);

        if (input == 10 || input == KEY_ENTER) {
            break;
        }

        if (input == KEY_UP) {
            menu->selected = (menu->selected == 0) ? 0 : menu->selected - 1;
        } else if (input == KEY_DOWN) {
            menu->selected = (menu->selected + 1 >= menu->number_of_items) ? menu->selected : menu->selected + 1;
        }
    }

    return menu->actions[menu->selected];
}

void destroy_menu(menu_t *menu) {
    delwin(menu->window);

    for (int i = 0; i < menu->number_of_items; i++) {
        free(menu->options[i]);
    }
    free(menu);
}