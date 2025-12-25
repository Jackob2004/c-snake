#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <stddef.h>

typedef struct SnakeBody {
    double x;
    double y;
    double x_direction;
    double y_direction;
    char *symbol;
    int color_pair;
} body_part_t;

typedef struct Snake {
    double speed;
    size_t capacity;
    size_t length;
    body_part_t **body;
} snake_t;

snake_t *create_snake(double speed);

#endif //SNAKE_SNAKE_H