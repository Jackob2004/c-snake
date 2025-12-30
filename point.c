#include "point.h"

point_t calc_middle_position(const int target_width, const int target_height) {
    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    const int x = maxX / 2 - target_width / 2;
    const int y = maxY / 2 - target_height / 2;
    const point_t middle_point = {x, y};

    return middle_point;
}