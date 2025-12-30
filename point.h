#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H

#include <ncurses.h>

typedef struct Point {
    short unsigned int x;
    short unsigned int y;
} point_t;

point_t calc_middle_position(int target_width, int target_height);
#endif //SNAKE_POINT_H