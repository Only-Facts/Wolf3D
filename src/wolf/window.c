/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** window
*/

#include "my.h"

size_t init_window(data_t *data)
{
    sfVideoMode mode = {1920, 1080, 32};

    data->window = sfRenderWindow_create(mode, "WOLF_3D", sfClose, NULL);
    if (!data->window)
        return EXIT_ERROR;
    else
        sfRenderWindow_setFramerateLimit(data->window, 60);
    return EXIT_SUCCESS;
}
