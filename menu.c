#include "menu.h"

void add_trailing_spaces(const size_t number_of_items, const int max_length, char **strings) {
    for (int i = 0; i < number_of_items; i++) {
        char *new_option_ptr = malloc(max_length + 1 * sizeof(char));

        memset(new_option_ptr, ' ', max_length);
        new_option_ptr[max_length] = '\0';

        size_t len = strlen(strings[i]);
        len = (len > max_length) ? max_length: len;
        memcpy(new_option_ptr, strings[i], len);

        strings[i] = new_option_ptr;
    }
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

menu_t *create_menu(int columns, point_t point, size_t number_of_items, char **options, char *title, MenuAction *actions) {
    menu_t *menu = (menu_t *)malloc(sizeof(menu_t));
    menu->number_of_items = number_of_items;
    menu->options = options;
    menu->title = title;
    menu->actions = actions;

    const int OPTION_LENGTH = columns - 2;

    add_trailing_spaces(number_of_items, OPTION_LENGTH, options);

    menu->selected = 0;
    const int rows = (int)menu->number_of_items + 2;
    menu->window = newwin(rows, columns, point.y, point.x);
    box(menu->window, '|', 0);

    return menu;
}

void process_menu_input(menu_t *menu) {
    mvwprintw(menu->window, 0, 0, "%s", menu->title);
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

void destroy_menu(menu_t *menu) {
    delwin(menu->window);

    for (int i = 0; i < menu->number_of_items; i++) {
        free(menu->options[i]);
    }
    free(menu);
}