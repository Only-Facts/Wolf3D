/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** free.c
*/

#include "my.h"

void free_arr(char **arr)
{
    if (!arr)
        return;
    for (size_t i = 0; arr[i]; i++)
        if (arr[i])
            free(arr[i]);
    free(arr);
}
