#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include "ncurses.h"
#include "stdlib.h"

#define MAX_NAME_LENGTH 10

typedef struct Player {
    char *name;
    int score;
} player_t;

char *get_player_name();
#endif //SNAKE_PLAYER_H