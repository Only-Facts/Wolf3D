/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** scenes
*/

#include "my.h"

size_t loop(data_t *data)
{
    while (sfRenderWindow_isOpen(data->window)){
        sfRenderWindow_clear(data->window, sfBlack);
        sfRenderWindow_display(data->window);
    }
    return EXIT_SUCCESS;
}
