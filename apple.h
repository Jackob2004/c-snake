#ifndef SNAKE_APPLE_H
#define SNAKE_APPLE_H

#include <ncurses.h>
#include <stdbool.h>

typedef struct Apple {
    int x;
    int y;
    char *symbol;
    int color_pair;
    bool is_alive;
} apple_t;

apple_t *create_apple();
void respawn_apple(apple_t *apple, int maxX, int maxY);
void render_apple(const apple_t *apple, WINDOW *win);
void destroy_apple(apple_t *apple);

#endif //SNAKE_APPLE_H