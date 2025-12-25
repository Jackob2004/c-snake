#include "snake.h"

#include <stdlib.h>

snake_t *create_snake(const double speed) {
    snake_t *snake = malloc(sizeof(snake_t));
    snake->speed = speed;
    snake->length = 0;
    snake->capacity = 10;

    snake->body = malloc(sizeof(body_part_t) * snake->capacity);

    return snake;
}
