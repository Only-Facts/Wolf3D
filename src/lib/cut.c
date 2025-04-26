/*
** EPITECH PROJECT, 2025
** lib
** File description:
** cut
*/

#include "my.h"

static size_t check_sep(char c, const char *sep)
{
    if (!sep)
        return EXIT_FAIL;
    for (size_t i = 0; sep[i] != '\0'; i++)
        if (c == sep[i])
            return 1;
    return EXIT_SUCCESS;
}

static size_t word_len(const char *str, const char *sep)
{
    size_t len = 0;

    if (!str)
        return EXIT_FAIL;
    for (; check_sep(str[len], sep) != 1 && str[len] != '\0'; len++);
    return len;
}

static size_t count_word(const char *str, const char *sep)
{
    size_t count = 0;

    if (!str || !sep)
        return EXIT_FAIL;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (check_sep(str[i], sep) == 1)
            count++;
    return count;
}

static char **transfer_str(const char *str, char **array, const char *sep)
{
    size_t num_word = 0;
    size_t w_size = 0;
    size_t j = 0;

    if (!str || !sep)
        return NULL;
    num_word = count_word(str, sep);
    array = malloc(sizeof(char *) * (num_word + 2));
    if (!array)
        return NULL;
    for (size_t i = 0; str[i] != '\0'; i++)
        if (check_sep(str[i], sep) != 1){
            w_size = word_len(&str[i], sep);
            array[j] = strn_dup(&str[i], w_size);
            i += w_size;
            j++;
        }
    array[j] = NULL;
    return array;
}

char **cut(const char *str, const char *sep)
{
    char **array = NULL;

    if (!str || !sep)
        return NULL;
    array = transfer_str(str, array, (const char *)sep);
    if (!array)
        return NULL;
    return array;
}
