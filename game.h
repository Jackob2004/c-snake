#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "snake.h"
#include <time.h>

typedef struct GameState {
    snake_t *snake;
    WINDOW *game_window;
} game_state_t;

void start_game_loop();

#endif //SNAKE_GAME_H