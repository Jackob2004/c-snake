#include "apple.h"

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

void respawn_apple(apple_t *apple, const point_t point) {
    apple->position.x = point.x;
    apple->position.y = point.y;
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