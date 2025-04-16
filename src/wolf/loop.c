/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** scenes
*/

#include "my.h"
#include "macro.h"

size_t loop(data_t *data)
{
    while (sfRenderWindow_isOpen(data->window)){
        sfRenderWindow_clear(data->window, GREY);
        event(data);
        draw_player(data);
        sfRenderWindow_display(data->window);
    }
    return EXIT_SUCCESS;
}
