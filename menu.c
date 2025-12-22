#include "menu.h"

#include <stdlib.h>

menu_t *create_menu(int columns, point_t point, size_t number_of_items, char *options[number_of_items], void (*actions[number_of_items])()) {
    menu_t *menu = (menu_t *)malloc(sizeof(menu_t));
    menu->number_of_items = number_of_items;
    menu->options = options;
    menu->actions = actions;

    menu->selected = 0;
    const int rows = (int)menu->number_of_items + 2;
    menu->window = newwin(rows, columns, point.y, point.x);
    box(menu->window, '|', 0);

    return menu;
}

void update_menu(const menu_t *menu) {
    for (int i = 0; i < menu->number_of_items; i++) {
        if (i == menu->selected) {
            wattron(menu->window, A_REVERSE);
        }
        mvwprintw(menu->window,i+1, 1, "%s", menu->options[i]);
        wattroff(menu->window, A_REVERSE);
    }
}

void process_menu_input(menu_t *menu) {
    keypad(menu->window, true);

    while (1) {
        update_menu(menu);

        const int input = wgetch(menu->window);

        if (input == 10 || input == KEY_ENTER) {
            break;
        }

        if (input == KEY_UP) {
            menu->selected = (menu->selected == 0) ? 0 : menu->selected - 1;
        } else if (input == KEY_DOWN) {
            menu->selected = (menu->selected + 1 > menu->number_of_items - 1) ? menu->selected : menu->selected + 1;
        }
    }

    menu->actions[menu->selected]();
}
