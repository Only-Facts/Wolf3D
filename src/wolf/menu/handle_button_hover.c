/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** handle_button_hover.c
*/

#include "my.h"
#include "macro.h"
#include "struct.h"

static void handle_single_button_hover(sfText *button, sfVector2f world_pos)
{
    sfFloatRect bounds = sfText_getGlobalBounds(button);

    if (world_pos.x >= bounds.left && world_pos.x <= bounds.left +
        bounds.width &&
        world_pos.y >= bounds.top && world_pos.y <= bounds.top +
        bounds.height) {
        sfText_setFillColor(button, sfColor_fromRGB(180, 20, 30));
    } else {
        sfText_setFillColor(button, WHITE);
    }
}

void handle_button_hover(data_t *data)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(data->win);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(data->win,
        mouse_pos, NULL);

    handle_single_button_hover(data->menu->play, world_pos);
    handle_single_button_hover(data->menu->options, world_pos);
    handle_single_button_hover(data->menu->quit, world_pos);
}
