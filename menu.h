#ifndef SNAKE_MENU_H
#define SNAKE_MENU_H

#include <ncurses.h>

typedef struct Point {
    short unsigned int x;
    short unsigned int y;
} point_t;

typedef struct Menu {
    size_t number_of_items;
    size_t selected;
    char **options;
    WINDOW *window;
    void (**actions)();
} menu_t;

menu_t *create_menu(int columns, point_t point, size_t number_of_items, char *options[number_of_items], void (*actions[number_of_items])());

#endif //SNAKE_MENU_H