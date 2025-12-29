#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct SnakeBody {
    int x;
    int y;
    char *symbol;
    int color_pair;
} body_part_t;

typedef struct Snake {
    size_t capacity;
    size_t length;
    body_part_t **body;
    body_part_t ghost_tail;
    signed int x_direction : 2;
    signed int y_direction : 2;
} snake_t;

snake_t *create_snake(int x_start, int y_start);
void grow_snake(snake_t *snake);
void update_snake(snake_t *snake);
void render_snake(WINDOW *window, const snake_t *snake);
void change_snake_direction(snake_t *snake, int key_code);
bool collides_snake_head(const snake_t *snake, int x, int y);
bool snake_collides_itself(const snake_t *snake);
void destroy_snake(snake_t *snake);

#endif //SNAKE_SNAKE_H