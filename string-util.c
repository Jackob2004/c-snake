#include "string-util.h"

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

strings_t *init_strings() {
    strings_t *strings = malloc(sizeof(strings_t));
    if (strings == NULL) exit(EXIT_FAILURE);

    strings->length = 0;
    strings->capacity = 10;

    strings->items = malloc(strings->capacity * sizeof(char *));
    if (strings->items == NULL) exit(EXIT_FAILURE);

    return strings;
}

void destroy_strings(strings_t *strings) {
    for (int i = 0; i < strings->length; i++) {
        free(strings->items[i]);
    }

    free(strings->items);
}