#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

#include <ncurses.h>
#include <stdlib.h>
#include "point.h"
#include "string-util.h"

typedef void (*MenuAction)(void *ptr);

typedef struct Menu {
    size_t number_of_items;
    size_t selected;
    char **options;
    char *title;
    WINDOW *window;
    MenuAction *actions;
} menu_t;

menu_t *create_menu(int columns, point_t spawn_point, size_t number_of_items, char **options, char *title, MenuAction *actions);
MenuAction process_menu_input(menu_t *menu);
void destroy_menu(menu_t *menu);

#endif //SNAKE_MENU_H