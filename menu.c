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