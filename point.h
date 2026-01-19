#ifndef SNAKE_POINT_H
#define SNAKE_POINT_H

#include <ncurses.h>
#include <stdlib.h>

typedef struct Point {
    short unsigned int x;
    short unsigned int y;
} point_t;

point_t calc_middle_position(int target_width, int target_height,const WINDOW *win);
point_t random_point(int xMax, int yMax);
#endif //SNAKE_POINT_H