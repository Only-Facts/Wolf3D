/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** floor.c
*/

#include "my.h"
#include "macro.h"

void draw_floor(data_t *data)
{
    sfRectangleShape *floor = sfRectangleShape_create();
    sfColor color = sfColor_fromRGB(173, 168, 126);

    if (!floor)
        return;
    sfRectangleShape_setFillColor(floor, color);
    sfRectangleShape_setSize(floor, (sfVector2f){data->FOV * MAP_S, 250});
    sfRectangleShape_setPosition(floor,
        (sfVector2f){(WIDTH / 2) - (data->FOV * MAP_S / 2), 530});
    sfRenderWindow_drawRectangleShape(data->win, floor, NULL);
    sfRectangleShape_destroy(floor);
}
