#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>
#include "point.h"

typedef struct SnakeBody {
    char *symbol;
    int color_pair;
    point_t position;
} body_part_t;

typedef struct Snake {
    size_t capacity;
    size_t length;
    body_part_t *body;
    point_t ghost_tail_position;
    signed int x_direction : 2;
    signed int y_direction : 2;
} snake_t;

snake_t *create_snake(point_t spawn_point);
void grow_snake(snake_t *snake);
void update_snake(snake_t *snake);
void render_snake(WINDOW *window, const snake_t *snake);
void change_snake_direction(snake_t *snake, int key_code);
bool collides_snake_head(const snake_t *snake, int x, int y);
bool snake_collides_itself(const snake_t *snake);
void destroy_snake(snake_t *snake);

#endif //SNAKE_SNAKE_H