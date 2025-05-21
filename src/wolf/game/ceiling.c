/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** ceiling.c
*/

#include "my.h"
#include "macro.h"

void draw_ceiling(data_t *data)
{
    sfRectangleShape *ceiling = sfRectangleShape_create();
    sfColor color = sfColor_fromRGB(41, 28, 13);

    if (!ceiling)
        return;
    sfRectangleShape_setFillColor(ceiling, color);
    sfRectangleShape_setSize(ceiling, (sfVector2f){data->FOV * MAP_S, 250});
    sfRectangleShape_setPosition(ceiling, 
        (sfVector2f){(WIDTH / 2) - (data->FOV * MAP_S / 2), 285});
    sfRenderWindow_drawRectangleShape(data->win, ceiling, NULL);
    sfRectangleShape_destroy(ceiling);
}

