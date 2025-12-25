#include "snake.h"

snake_t *create_snake(const double speed, const double x_start, const double y_start) {
    snake_t *snake = malloc(sizeof(snake_t));

    if (snake == NULL) {
        exit(EXIT_FAILURE);
    }
    snake->speed = speed;
    snake->length = 0;
    snake->capacity = 10;

    snake->body = malloc(sizeof(body_part_t) * snake->capacity);

    if (snake->body == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
        body_part_t *body_part = malloc(sizeof(body_part_t));

        if (body_part == NULL) {
            exit(EXIT_FAILURE);
        }

        body_part->x = x_start - i;
        body_part->y = y_start;
        body_part->x_direction = 1;
        body_part->y_direction = 0;
        body_part->symbol = "*";
        body_part->color_pair = 1;

        snake->body[i] = body_part;
        snake->length++;
    }

    return snake;
}

void grow_snake(snake_t *snake) {
    if (snake->length == snake->capacity) {
        snake->capacity *= 2;
        body_part_t **temp= realloc(snake->body, sizeof(body_part_t) * snake->capacity);

        if (temp == NULL) {
            exit(EXIT_FAILURE);
        }

        snake->body = temp;
    }

    body_part_t *body_part = malloc(sizeof(body_part_t));
    if (snake->body == NULL) {
        exit(EXIT_FAILURE);
    }
    const body_part_t *next = snake->body[snake->length - 1];
    body_part->symbol = "*";
    body_part->color_pair = 1;
    body_part->x_direction = next->x_direction;
    body_part->y_direction = next->y_direction;
    body_part->x = next->x - next->x_direction;
    body_part->y = next->y - next->y_direction;

    snake->body[snake->length] = body_part;
    snake->length++;
}

void render_snake(WINDOW *window, const snake_t *snake) {
    for (int i = 0; i < snake->length; i++) {
        attron(COLOR_PAIR(snake->body[i]->color_pair));
        mvwprintw(window, (int)snake->body[i]->y, (int)snake->body[i]->x, "%s", snake->body[i]->symbol);
        attroff(COLOR_PAIR(snake->body[i]->color_pair));
    }
}