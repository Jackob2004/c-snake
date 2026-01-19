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

char *str_from_user_input(int max_size);
char *int_to_str(int number, int size);
char *concatenate(const char *a, const char *b, const char *c);
void add_trailing_spaces(size_t number_of_items, int max_length, char **strings);
strings_t *init_strings();
void destroy_strings(strings_t *strings);

#endif //SNAKE_STRING_UTIL_H