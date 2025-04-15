/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** scenes
*/

#include "my.h"

size_t loop(data_t *data)
{
    if (init_window(data) == EXIT_ERROR)
        return EXIT_ERROR;
    while (sfRenderWindow_isOpen(data->window)){
        sfRenderWindow_clear(data->window, sfBlack);
        sfRenderWindow_display(data->window);
    }
    sfRenderWindow_destroy(data->window);
    return EXIT_SUCCESS;
}
