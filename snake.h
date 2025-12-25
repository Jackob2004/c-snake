#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct SnakeBody {
    double x;
    double y;
    char *symbol;
    int color_pair;
    signed int x_direction : 2;
    signed int y_direction : 2;
} body_part_t;

typedef struct Snake {
    double speed;
    size_t capacity;
    size_t length;
    body_part_t **body;
} snake_t;

snake_t *create_snake(double speed, double x_start, double y_start);
void grow_snake(snake_t *snake);
void update_snake(const snake_t *snake);
void render_snake(WINDOW *window, const snake_t *snake);
void change_snake_direction(const snake_t *snake, int key_code);

#endif //SNAKE_SNAKE_H