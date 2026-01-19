#include "string-util.h"

char *str_from_user_input(const int max_size) {
    char *str = malloc(sizeof(char) * (max_size + 1));
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

char *int_to_str(const int number, const int size) {
    char *str = malloc(sizeof(char) * (size + 1));
    sprintf(str, "%d", number);

    return str;
}

char *concatenate(const char *a, const char *b, const char *c) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    size_t clen = strlen(c);
    char *res = malloc(alen + blen + clen + 1);

    if (res == NULL) {
        exit(EXIT_FAILURE);
    }

    memcpy(res, a, alen);
    memcpy(res + alen, b, blen);
    memcpy(res + alen + blen, c, clen + 1);

    return res;
}

void add_trailing_spaces(const size_t number_of_items, const int max_length, char **strings) {
    for (int i = 0; i < number_of_items; i++) {
        char *new_option_ptr = malloc((max_length + 1) * sizeof(char));

        if (new_option_ptr == NULL) {
            exit(EXIT_FAILURE);
        }

        memset(new_option_ptr, ' ', max_length);
        new_option_ptr[max_length] = '\0';

        size_t len = strlen(strings[i]);
        len = (len > max_length) ? max_length: len;
        memcpy(new_option_ptr, strings[i], len);

        strings[i] = new_option_ptr;
    }
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