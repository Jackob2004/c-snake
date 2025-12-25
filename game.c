#include "game.h"

game_state_t *init_game() {
    game_state_t *game_state = malloc(sizeof(game_state_t));
    if (game_state == NULL) {
        exit(EXIT_FAILURE);
    }

    init_pair(1, COLOR_GREEN, COLOR_BLACK);

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

    game_state->snake = create_snake(5,5);

    return game_state;
}

void process_input(const game_state_t *game_state, const int key) {
    change_snake_direction(game_state->snake, key);
    if (key == KEY_BACKSPACE) grow_snake(game_state->snake);
}

void update(const game_state_t *game_state) {
    update_snake(game_state->snake);
}

void render(const game_state_t *game_state) {
    render_snake(game_state->game_window, game_state->snake);
    box(game_state->game_window, 0, 0);
}

void start_game_loop() {
    game_state_t *game_state = init_game();

    const double MS_PER_UPDATE = 150.0;
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
    double lag = 0.0;
    int input;
    while ((input = wgetch(game_state->game_window)) != 'q') {
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

    destroy_snake(game_state->snake);
    delwin(game_state->game_window);
    free(game_state);
}