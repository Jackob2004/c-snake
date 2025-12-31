#ifndef SNAKE_PLAYER_H
#define SNAKE_PLAYER_H

#include "ncurses.h"
#include "stdlib.h"
#include "array.h"

#define MAX_NAME_LENGTH 10
#define STATS_FILE_NAME "player.csv"

typedef struct Player {
    char *name;
    int score;
} player_t;

typedef struct Players {
    size_t length;
    size_t capacity;
    player_t *items;
} players_t;

char *get_player_name();
void save_player_best_score(player_t player);
#endif //SNAKE_PLAYER_H