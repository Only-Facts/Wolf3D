/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw.c
*/

#include "my.h"

void draw_player(data_t *data)
{
    sfRectangleShape_setPosition(data->player->texture, data->player->pos);
    sfSprite_setPosition(data->player->sprite, data->player->pos);
    sfRenderWindow_drawRectangleShape(data->window, data->player->texture, NULL);
}
