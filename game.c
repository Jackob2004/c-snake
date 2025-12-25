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

    game_state->snake = create_snake(1, maxX / 2, maxY / 2);

    return game_state;
}

void process_input(game_state_t *game_state) {

}

void update(game_state_t *game_state) {

}

void render(game_state_t *game_state) {

}

