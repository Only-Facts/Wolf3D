/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** player.c
*/

#include "my.h"
#include "macro.h"

size_t init_player(data_t *data)
{
    data->p = malloc(sizeof(player_t));

    data->p->color = GREEN;
    data->p->pos = (sfVector2f){(double)MAP_X * MAP_S / 2, (double)MAP_Y * MAP_S / 2};
    data->p->texture = sfRectangleShape_create();
    data->p->angle = 0;
    data->p->delta = (sfVector2f){0.0, 0.0};
    if (!data->p->texture)
        return EXIT_ERROR;
    sfRectangleShape_setSize(data->p->texture, (sfVector2f){6, 6});
    sfRectangleShape_setPosition(data->p->texture, data->p->pos);
    sfRectangleShape_setFillColor(data->p->texture, data->p->color);
    return EXIT_SUCCESS;
}
