#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "snake.h"
#include <time.h>
#include "main-menu.h"
#include "menu.h"
#include "apple.h"
#include "player.h"

typedef enum GAME_STATUS {
    RUNNING,
    OVER,
    PAUSED
} game_status_t;

typedef struct GameState {
    snake_t *snake;
    apple_t *apple;
    game_status_t status;
    WINDOW *game_window;
    int window_height;
    int window_width;
    player_t player;
} game_state_t;

void start_game_loop();

#endif //SNAKE_GAME_H