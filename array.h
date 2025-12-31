#ifndef SNAKE_ARRAY_H
#define SNAKE_ARRAY_H

#define array_append(array, item)\
    do {\
        if (array->length == array->capacity) {\
            array->capacity *= 2;\
            void *temp = realloc(array->items, sizeof(*array->items) * array->capacity);\
            if (temp == NULL) exit(EXIT_FAILURE);\
            array->items = temp;\
        }\
        array->items[array->length] = item;\
        array->length++;\
    } while (0)

#endif //SNAKE_ARRAY_H