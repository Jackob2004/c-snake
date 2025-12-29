#include "snake.h"

snake_t *create_snake(const point_t spawn_point) {
    snake_t *snake = malloc(sizeof(snake_t));

    if (snake == NULL) {
        exit(EXIT_FAILURE);
    }
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

        body_part->position.x = spawn_point.x - i;
        body_part->position.y = spawn_point.y;
        body_part->symbol = "*";
        body_part->color_pair = 1;

        snake->body[i] = body_part;
        snake->length++;
    }

    snake->x_direction = 1;
    snake->y_direction = 0;
    snake->ghost_tail_position.x = snake->body[snake->length - 1]->position.x;
    snake->ghost_tail_position.y = snake->body[snake->length - 1]->position.y;

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

    body_part->symbol = "*";
    body_part->color_pair = 1;
    body_part->position.x = snake->ghost_tail_position.x;
    body_part->position.y = snake->ghost_tail_position.y;

    snake->body[snake->length] = body_part;
    snake->length++;
}

void update_snake(snake_t *snake) {
    snake->ghost_tail_position.x = snake->body[snake->length - 1]->position.x;
    snake->ghost_tail_position.y = snake->body[snake->length - 1]->position.y;

    for (int i = (int)snake->length - 1; i > 0; i--) {
        snake->body[i]->position.x = snake->body[i - 1]->position.x;
        snake->body[i]->position.y = snake->body[i - 1]->position.y;
    }

    snake->body[0]->position.x += snake->x_direction;
    snake->body[0]->position.y += snake->y_direction;
}

void render_snake(WINDOW *window, const snake_t *snake) {
    for (int i = 0; i < snake->length; i++) {
        wattron(window, COLOR_PAIR(snake->body[i]->color_pair));
        mvwprintw(window, snake->body[i]->position.y, snake->body[i]->position.x, "%s", snake->body[i]->symbol);
        wattroff(window, COLOR_PAIR(snake->body[i]->color_pair));
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

bool collides_snake_head(const snake_t *snake, const int x, const int y) {
    const body_part_t *head = snake->body[0];
    return head->position.x == x && head->position.y == y;
}

bool snake_collides_itself(const snake_t *snake) {
    for (int i = 1; i < snake->length; i++) {
        if (collides_snake_head(snake, snake->body[i]->position.x, snake->body[i]->position.y)) {
            return true;
        }
    }

    return false;
}

void destroy_snake(snake_t *snake) {
    for (int i = 0; i < snake->length; i++) {
        free(snake->body[i]);
    }

    free(snake->body);
    free(snake);
}