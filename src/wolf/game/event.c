/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** event.c
*/

#include "my.h"
#include "macro.h"
#include <math.h>

static void reset_keys(data_t *data)
{
    data->keys->z = 0;
    data->keys->s = 0;
    data->keys->d = 0;
    data->keys->q = 0;
    data->keys->left = 0;
    data->keys->right = 0;
}

size_t init_keys(data_t *data)
{
    data->keys = malloc(sizeof(keys_t));
    if (!data->keys)
        return EXIT_ERROR;
    reset_keys(data);
    return EXIT_SUCCESS;
}

static void update_camera(data_t *data)
{
    if (data->keys->right) {
        data->p->angle += 0.06 * data->dtime;
        if (data->p->angle > 2 * PI)
            data->p->angle -= 2 * PI;
    }
    if (data->keys->left) {
        data->p->angle -= 0.06 * data->dtime;
        if (data->p->angle < 0)
            data->p->angle += 2 * PI;
    }
}

static void forward_backward(data_t *data)
{
    if (data->keys->z) {
        if (data->map->map[data->p->ip.y][data->p->ippo.x] == 0)
            data->p->pos.x += cos(data->p->angle) * data->dtime;
        if (data->map->map[data->p->ippo.y][data->p->ip.x] == 0)
            data->p->pos.y += sin(data->p->angle) * data->dtime;
    }
    if (data->keys->s) {
        if (data->map->map[data->p->ip.y][data->p->ipmo.x] == 0)
            data->p->pos.x -= cos(data->p->angle) * data->dtime;
        if (data->map->map[data->p->ipmo.y][data->p->ip.x] == 0)
            data->p->pos.y -= sin(data->p->angle) * data->dtime;
    }
}

static void left_right(data_t *data)
{
    if (data->keys->d) {
        if (data->map->map[data->p->ip.y][data->p->jppo.x] == 0)
            data->p->pos.x += cos(data->p->angle + 90 * RAD) * data->dtime;
        if (data->map->map[data->p->jppo.y][data->p->ip.x] == 0)
            data->p->pos.y += sin(data->p->angle + 90 * RAD) * data->dtime;
    }
    if (data->keys->q) {
        if (data->map->map[data->p->ip.y][data->p->jpmo.x] == 0)
            data->p->pos.x += cos(data->p->angle - 90 * RAD) * data->dtime;
        if (data->map->map[data->p->jpmo.y][data->p->ip.x] == 0)
            data->p->pos.y += sin(data->p->angle - 90 * RAD) * data->dtime;
    }
}

static void update_movement(data_t *data)
{
    forward_backward(data);
    left_right(data);
}

static void update_keys(data_t *data)
{
    if (sfKeyboard_isKeyPressed(sfKeyZ))
        data->keys->z = 1;
    if (sfKeyboard_isKeyPressed(sfKeyS))
        data->keys->s = 1;
    if (sfKeyboard_isKeyPressed(sfKeyD))
        data->keys->d = 1;
    if (sfKeyboard_isKeyPressed(sfKeyQ))
        data->keys->q = 1;
    if (sfKeyboard_isKeyPressed(sfKeyLeft))
        data->keys->left = 1;
    if (sfKeyboard_isKeyPressed(sfKeyRight))
        data->keys->right = 1;
}

static void check_walls_lr(data_t *data)
{
    sfVector2i o = {0, 0};
    sfVector2f p = {data->p->pos.x, data->p->pos.y};

    if (cos(data->p->angle + 90 * RAD) < 0)
        o.x = -8;
    o.x += 4;
    if (sin(data->p->angle + 90 * RAD) < 0)
        o.y = -8;
    o.y += 4;
    data->p->jppo = (sfVector2i){(p.x + o.x) / (float)MAP_S,
        (p.y + o.y) / (float)MAP_S};
    data->p->jpmo = (sfVector2i){(p.x - o.x) / (float)MAP_S,
        (p.y - o.y) / (float)MAP_S};
}

static void check_walls(data_t *data)
{
    sfVector2i o = {0, 0};
    sfVector2f p = {data->p->pos.x, data->p->pos.y};

    data->p->ip = (sfVector2i){p.x / (float)MAP_S, p.y / (float)MAP_S};
    if (cos(data->p->angle) < 0)
        o.x = -8;
    o.x += 4;
    if (sin(data->p->angle) < 0)
        o.y = -8;
    o.y += 4;
    data->p->ippo = (sfVector2i){(p.x + o.x) / (float)MAP_S,
        (p.y + o.y) / (float)MAP_S};
    data->p->ipmo = (sfVector2i){(p.x - o.x) / (float)MAP_S,
        (p.y - o.y) / (float)MAP_S};
    check_walls_lr(data);
}

void event(data_t *data)
{
    sfEvent event = {.type = sfEvtKeyPressed};

    sfRenderWindow_pollEvent(data->win, &event);
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(data->win);
    else if (sfKeyboard_isKeyPressed(sfKeyM))
        data->scenes = MENU;
    update_keys(data);
    check_walls(data);
    update_movement(data);
    update_camera(data);
    reset_keys(data);
}
