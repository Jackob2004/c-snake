#include "snake.h"

snake_t *create_snake(const double speed, const double x_start, const double y_start) {
    snake_t *snake = malloc(sizeof(snake_t));
    snake->speed = speed;
    snake->length = 0;
    snake->capacity = 10;

    snake->body = malloc(sizeof(body_part_t) * snake->capacity);

    for (int i = 0; i < 3; i++) {
        body_part_t *body_part = malloc(sizeof(body_part_t));

        body_part->x = x_start - i;
        body_part->y = y_start;
        body_part->x_direction = 1;
        body_part->y_direction = 0;
        body_part->symbol = '*';

        snake->body[i] = body_part;
        snake->length++;
    }

    return snake;
}

