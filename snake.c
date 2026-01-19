#include "snake.h"

snake_t *create_snake(const point_t spawn_point) {
    snake_t *snake = malloc(sizeof(snake_t));

    if (snake == NULL) {
        exit(EXIT_FAILURE);
    }
    snake->length = 0;
    snake->capacity = 10;

    snake->items = malloc(sizeof(body_part_t) * snake->capacity);

    if (snake->items == NULL) {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++) {
        const body_part_t body_part = {
            .position = {spawn_point.x - i,spawn_point.y},
            .symbol = "*",
            .color_pair = 1
        };

        snake->items[i] = body_part;
        snake->length++;
    }

    snake->x_direction = 1;
    snake->y_direction = 0;
    snake->ghost_tail_position.x = snake->items[snake->length - 1].position.x;
    snake->ghost_tail_position.y = snake->items[snake->length - 1].position.y;

    return snake;
}

void grow_snake(snake_t *snake) {
    const body_part_t body_part = {
        .position = {snake->ghost_tail_position.x, snake->ghost_tail_position.y},
        .symbol = "*",
        .color_pair = 1
    };

    array_append(snake, body_part);
}

void update_snake(snake_t *snake) {
    snake->ghost_tail_position.x = snake->items[snake->length - 1].position.x;
    snake->ghost_tail_position.y = snake->items[snake->length - 1].position.y;

    for (int i = (int)snake->length - 1; i > 0; i--) {
        snake->items[i].position.x = snake->items[i - 1].position.x;
        snake->items[i].position.y = snake->items[i - 1].position.y;
    }

    snake->items[0].position.x += snake->x_direction;
    snake->items[0].position.y += snake->y_direction;
}

void render_snake(WINDOW *window, const snake_t *snake) {
    for (int i = 0; i < snake->length; i++) {
        wattron(window, COLOR_PAIR(snake->items[i].color_pair));
        mvwprintw(window, snake->items[i].position.y, snake->items[i].position.x, "%s", snake->items[i].symbol);
        wattroff(window, COLOR_PAIR(snake->items[i].color_pair));
    }
}

void change_snake_direction(snake_t *snake, const int key_code) {
    switch (key_code) {
        case KEY_UP:
            if (snake->y_direction == 1) break;
            snake->y_direction = -1;
            snake->x_direction = 0;
            break;
        case KEY_DOWN:
            if (snake->y_direction == -1) break;
            snake->y_direction = 1;
            snake->x_direction = 0;
            break;
        case KEY_LEFT:
            if (snake->x_direction == 1) break;
            snake->x_direction = -1;
            snake->y_direction = 0;
            break;
        case KEY_RIGHT:
            if (snake->x_direction == -1) break;
            snake->y_direction = 0;
            snake->x_direction = 1;
            break;
        default: ;
    }
}

bool collides_snake_head(const snake_t *snake, const point_t point) {
    const body_part_t head = snake->items[0];
    return head.position.x == point.x && head.position.y == point.y;
}

bool snake_collides_itself(const snake_t *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (collides_snake_head(snake, snake->items[i].position)) {
            return true;
        }
    }

    return false;
}

bool collides_snake_body(const snake_t *snake, const point_t position) {
    for (int i = 1; i < snake->length; i++) {
        if (snake->items[i].position.x == position.x && snake->items[i].position.y == position.y) {
            return true;
        }
    }

    return false;
}

void destroy_snake(snake_t *snake) {
    free(snake->items);
    free(snake);
}