/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** player.c
*/

#include "my.h"
#include "macro.h"

void init_player(data_t *data)
{
    data->player = malloc(sizeof(player_t));

    data->player->sprite = sfSprite_create();
    data->player->color = GREEN;
    data->player->pos = (sfVector2f){WIDTH / 2.0, HEIGHT / 2.0};
    data->player->texture = sfRectangleShape_create();
    sfRectangleShape_setSize(data->player->texture, (sfVector2f){5, 5});
    sfRectangleShape_setPosition(data->player->texture, data->player->pos);
    sfRectangleShape_setFillColor(data->player->texture, data->player->color);
}
