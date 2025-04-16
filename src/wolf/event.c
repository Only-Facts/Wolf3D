/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** event.c
*/

#include "my.h"

void quit(data_t *data, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(data->window);
}

void update_movement(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        data->player->pos.y--;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        data->player->pos.y++;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        data->player->pos.x++;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        data->player->pos.x--;
}

void event(data_t *data)
{
    sfEvent event; 

    sfRenderWindow_pollEvent(data->window, &event);
    quit(data, event);
    update_movement(data);
}
