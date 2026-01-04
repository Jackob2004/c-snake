#include "game.h"

#include "player.h"

game_state_t *init_game(char *player_name) {
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

    const player_t player = {player_name, 0};
    game_state->player = player;

    return game_state;
}

void play_again_menu() {
    const int COLUMNS = 50;
    point_t spawn_point = calc_middle_position(COLUMNS, 1, stdscr);
    spawn_point.y = 5;

    char *options[] = {"Yes", "No"};
    MenuAction actions[] = {start_game_loop, main_menu};

    menu_t *menu = create_menu(COLUMNS, spawn_point, 2, options, "Do you want to play again ?", actions);

    const MenuAction chosen_action = process_menu_input(menu);
    destroy_menu(menu);

    clear();
    refresh();
    chosen_action(NULL);
}

void game_over(game_state_t *game_state) {
    const int player_best_score = save_player_best_score(game_state->player);
    box(game_state->game_window, 0, 0);
    mvwprintw(game_state->game_window, 0,0,"GAME OVER!!! %s Final Score: %d Best Score: %d",
        game_state->player.name, game_state->player.score, player_best_score);
    wrefresh(game_state->game_window);
    game_state->status = OVER;
}

void process_input(game_state_t *game_state, const int key) {
    if (key == 'q') {
        game_state->status = OVER;
    }

    if (key == 'p') {
        game_state->status = (game_state->status == PAUSED) ? RUNNING : PAUSED;
        mvwprintw(game_state->game_window, 0,0, "Game Paused");
    }

    change_snake_direction(game_state->snake, key);
}

void update(game_state_t *game_state) {
    if (snake_collides_itself(game_state->snake)) {
        game_over(game_state);
        return;
    }

    const body_part_t head = game_state->snake->items[0];
    const bool reached_map_boundaries = head.position.x >= game_state->window_width - 1 || head.position.x <= 0 ||
        head.position.y >= game_state->window_height - 1 || head.position.y <= 0;

    if (reached_map_boundaries) {
        game_over(game_state);
        return;
    }

    if (collides_snake_head(game_state->snake, game_state->apple->position.x, game_state->apple->position.y)) {
        respawn_apple(game_state->apple, game_state->window_width, game_state->window_height);
        grow_snake(game_state->snake);
        game_state->player.score += 1;
    }

    update_snake(game_state->snake);
}

void render(const game_state_t *game_state) {
    render_snake(game_state->game_window, game_state->snake);
    render_apple(game_state->apple, game_state->game_window);
    box(game_state->game_window, 0, 0);
    mvwprintw(game_state->game_window, 0,0,"Player: %s Score: %d", game_state->player.name, game_state->player.score);
}

void game_clear_up(game_state_t *game_state) {
    destroy_snake(game_state->snake);
    destroy_apple(game_state->apple);
    delwin(game_state->game_window);
    free(game_state->player.name);
    free(game_state);
}

void start_game_loop(void *ptr) {
    game_state_t *game_state = init_game(get_player_name());

    const double MS_PER_UPDATE = 150.0;
    struct timespec last_time;
    clock_gettime(CLOCK_MONOTONIC, &last_time);
    double lag = 0.0;
    while (game_state->status == RUNNING || game_state->status == PAUSED) {
        const int input = wgetch(game_state->game_window);

        process_input(game_state, input);
        if (game_state->status == PAUSED) {
            clock_gettime(CLOCK_MONOTONIC, &last_time);
            continue;
        }
        werase(game_state->game_window);

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        const double elapsed = (double)(current_time.tv_sec - last_time.tv_sec) * 1000.0 +
            (double)(current_time.tv_nsec - last_time.tv_nsec) / 1000000.0;
        last_time = current_time;
        lag += elapsed;

        while (lag >= MS_PER_UPDATE) {
            update(game_state);
            lag -= MS_PER_UPDATE;
        }

        render(game_state);
    }

    game_clear_up(game_state);
    play_again_menu();
}
