#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include <curses.h>
#include <stdbool.h>
#include <stdlib.h>
#include "point.h"

typedef struct Apple {
    point_t position;
    char *symbol;
    int color_pair;
    bool is_alive;
} apple_t;

apple_t *create_apple();
void respawn_apple(apple_t *apple, point_t point);
void render_apple(const apple_t *apple, WINDOW *win);
void destroy_apple(apple_t *apple);

#endif //SNAKE_APPLE_H