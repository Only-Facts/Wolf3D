/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** window
*/

#include "my.h"

size_t init_wind_set(data_t *data)
{
    sfVideoMode mode = {1920, 1080, 32};

    data->window = sfRenderWindow_create(mode, "WOLF_3D", sfClose, NULL);
    if (!data->window)
        return EXIT_ERROR;
    else
        sfRenderWindow_setFramerateLimit(data->window, 60);
    return EXIT_SUCCESS;
}

size_t init_window(data_t *data){
    if (init_wind_set(data) == EXIT_ERROR)
        return EXIT_ERROR;
    while (sfRenderWindow_isOpen(data->window)){
        sfRenderWindow_clear(data->window, sfBlack);
        sfRenderWindow_display(data->window);
    }
    sfRenderWindow_destroy(data->window);
    return EXIT_SUCCESS;
}
