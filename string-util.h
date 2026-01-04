#ifndef SNAKE_STRING_UTIL_H
#define SNAKE_STRING_UTIL_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

typedef struct Strings {
    size_t length;
    size_t capacity;
    char **items;
} strings_t;

char *get_str(int max_size);
char *int_to_str(int number, int size);
char *concatenate(const char *a, const char *b, const char *c);
strings_t *init_strings();
void destroy_strings(strings_t *strings);

#endif //SNAKE_STRING_UTIL_H