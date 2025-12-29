#include "apple.h"

#include <stdlib.h>
#include <time.h>

apple_t *create_apple() {
    apple_t *apple = (apple_t *)malloc(sizeof(apple_t));
    if (apple == NULL) {
        exit(EXIT_FAILURE);
    }

    apple->color_pair = 2;
    apple->symbol = "+";
    apple->is_alive = false;

    return apple;
}

void respawn_apple(apple_t *apple, const int maxX, const int maxY) {
    const int x = (rand() % (maxX - 2)) + 1;
    const int y = (rand() % (maxY - 2)) + 1;

    apple->position.x = x;
    apple->position.y = y;
    apple->is_alive = true;
}

void render_apple(const apple_t *apple, WINDOW *win) {
    if (!apple->is_alive) return;

    wattron(win, COLOR_PAIR(apple->color_pair));
    mvwprintw(win, apple->position.y, apple->position.x, "%s", apple->symbol);
    wattroff(win, COLOR_PAIR(apple->color_pair));
}

void destroy_apple(apple_t *apple) {
    free(apple);
}