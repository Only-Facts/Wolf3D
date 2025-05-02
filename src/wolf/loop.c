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
    if (display_menu(data) == EXIT_ERROR)
        return EXIT_ERROR;
    while (sfRenderWindow_isOpen(data->win)){
        sfRenderWindow_clear(data->win, GREY);
        event(data);
        draw(data);
        sfRenderWindow_display(data->win);
    }
    return EXIT_SUCCESS;
}
