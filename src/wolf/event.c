/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** event.c
*/

#include "my.h"
#include "macro.h"
#include <SFML/Window/Keyboard.h>
#include <math.h>

static void quit(data_t *data, sfEvent event)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(data->win);
}

static void update_camera(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        data->p->angle += 0.08;
        if (data->p->angle > 2 * PI)
            data->p->angle -= 2 * PI;
    }
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        data->p->angle -= 0.08;
        if (data->p->angle < 0)
            data->p->angle += 2 * PI;
    }
}

static void update_movement(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ)) {
        data->p->pos.x += cos(data->p->angle);
        data->p->pos.y += sin(data->p->angle);
    }
    if (sfKeyboard_isKeyPressed(sfKeyS)) {
        data->p->pos.x -= cos(data->p->angle);
        data->p->pos.y -= sin(data->p->angle);
    }
    if (sfKeyboard_isKeyPressed(sfKeyD)) {
        data->p->pos.x += cos(data->p->angle + 90 * RAD);
        data->p->pos.y += sin(data->p->angle + 90 * RAD);
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ)) {
        data->p->pos.x += cos(data->p->angle - 90 * RAD);
        data->p->pos.y += sin(data->p->angle - 90 * RAD);
    }
    update_camera(data);
}

void event(data_t *data)
{
    sfEvent event;

    sfRenderWindow_pollEvent(data->win, &event);
    quit(data, event);
    update_movement(data);
}
