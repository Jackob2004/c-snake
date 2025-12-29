#include "game.h"

game_state_t *init_game() {
    game_state_t *game_state = malloc(sizeof(game_state_t));
    if (game_state == NULL) {
        exit(EXIT_FAILURE);
    }

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    const int ROWS = maxY / 2;
    const int COLUMNS = maxX / 2;
    const int X_POS = maxX / 2 - (COLUMNS / 2);
    const int Y_POS = maxY / 2 - (ROWS / 2);

    game_state->game_window = newwin(ROWS, COLUMNS, Y_POS, X_POS);
    box(game_state->game_window, 0, 0);
    nodelay(game_state->game_window, TRUE);
    keypad(game_state->game_window, TRUE);

    game_state->status = RUNNING;
    getmaxyx(game_state->game_window, game_state->window_height, game_state->window_width);

    const point_t spawn_point = {5,5};
    game_state->snake = create_snake(spawn_point);
    game_state->apple = create_apple();
    respawn_apple(game_state->apple, game_state->window_width, game_state->window_height);

    return game_state;
}

void game_over(game_state_t *game_state) {
    box(game_state->game_window, 0, 0);
    mvwprintw(game_state->game_window, 0,0,"GAME OVER");
    wrefresh(game_state->game_window);
    game_state->status = OVER;
}

void process_input(game_state_t *game_state, const int key) {
    if (key == 'q') {
        game_state->status = OVER;
    }
    change_snake_direction(game_state->snake, key);
}

void update(game_state_t *game_state) {
    if (collides_snake_head(game_state->snake, game_state->apple->position.x, game_state->apple->position.y)) {
        respawn_apple(game_state->apple, game_state->window_width, game_state->window_height);
        grow_snake(game_state->snake);
    }

    if (snake_collides_itself(game_state->snake)) {
        game_over(game_state);
    }

    const body_part_t *head = game_state->snake->body[0];
    const bool reached_map_boundaries = head->position.x >= game_state->window_width - 1 || head->position.x <= 0 ||
        head->position.y >= game_state->window_height - 1 || head->position.y <= 0;

    if (reached_map_boundaries) {
        game_over(game_state);
    }

    update_snake(game_state->snake);
}

void render(const game_state_t *game_state) {
    render_snake(game_state->game_window, game_state->snake);
    render_apple(game_state->apple, game_state->game_window);
    box(game_state->game_window, 0, 0);
}

void game_clear_up(game_state_t *game_state) {
    destroy_snake(game_state->snake);
    destroy_apple(game_state->apple);
    delwin(game_state->game_window);
    free(game_state);
}

void start_game_loop() {
    game_state_t *game_state = init_game();

    const double MS_PER_UPDATE = 150.0;
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
    double lag = 0.0;
    while (game_state->status == RUNNING) {
        const int input = wgetch(game_state->game_window);
        werase(game_state->game_window);

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        const double elapsed = (double)(current_time.tv_sec - last_time.tv_sec) * 1000.0 +
            (double)(current_time.tv_nsec - last_time.tv_nsec) / 1000000.0;
        last_time = current_time;
        lag += elapsed;

        process_input(game_state, input);

        while (lag >= MS_PER_UPDATE) {
            update(game_state);
            lag -= MS_PER_UPDATE;
        }

        render(game_state);
    }

    game_clear_up(game_state);
}
