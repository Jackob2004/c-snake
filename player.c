#include "player.h"

#include <string.h>

#include "point.h"

char *get_str(const int max_size) {
    char *str = malloc(sizeof(char) * max_size + 1);
    int idx = 0;

    nocbreak();
    echo();

    int c = getch();

    while (c != '\n' && idx < max_size) {
        str[idx] = (char)c;
        c = getch();
        idx++;
    }

    const int end = (idx < max_size) ? idx : max_size;
    str[end] = '\0';

    cbreak();
    noecho();

    return str;
}

char *get_player_name() {
    const char info[] = "Enter your name: ";
    const point_t center = calc_middle_position(strlen(info),1);
    mvprintw(center.y - 1, center.x, info);

    char underline[MAX_NAME_LENGTH + 1];
    memset(underline, '_', MAX_NAME_LENGTH);
    underline[MAX_NAME_LENGTH] = '\0';

    mvprintw(center.y + 1, center.x, "%s", underline);
    move(center.y + 1, center.x);
    char *name = get_str(MAX_NAME_LENGTH);

    if (strlen(name) == 0) {
        strcpy(name, "unknown");
    }

    clear();
    refresh();

    return name;
}