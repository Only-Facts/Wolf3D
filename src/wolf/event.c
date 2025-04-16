/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** event.c
*/

#include "my.h"
#include "macro.h"
#include <math.h>

static void quit(data_t *data, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(data->win);
}

static void update_movement(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        data->p->pos.x += data->p->delta.x;
        data->p->pos.y += data->p->delta.y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        data->p->pos.x -= data->p->delta.x;
        data->p->pos.y -= data->p->delta.y;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        data->p->angle += 0.08;
        if (data->p->angle > 2 * PI)
            data->p->angle -= 2 * PI;
        data->p->delta.x = cos(data->p->angle) * 2;
        data->p->delta.y = sin(data->p->angle) * 2;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        data->p->angle -= 0.08;
        if (data->p->angle < 0)
            data->p->angle += 2 * PI;
        data->p->delta.x = cos(data->p->angle) * 2;
        data->p->delta.y = sin(data->p->angle) * 2;
    }
}

void event(data_t *data)
{
    sfEvent event; 

    sfRenderWindow_pollEvent(data->win, &event);
    quit(data, event);
    update_movement(data);
}
