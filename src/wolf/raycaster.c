/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** raycaster.c
*/

#include "my.h"
#include "macro.h"
#include <math.h>

size_t init_ray(data_t *data)
{
    data->r = malloc(sizeof(ray_t));
    if (!data->r)
        return EXIT_ERROR;
    data->r->angle = data->p->angle;
    return EXIT_SUCCESS;
}

static float distance(sfVector2f a, sfVector3f b)
{
    sfVector2f dist = {a.x - b.x, a.y - b.y};

    return ((dist.x * dist.x) + (dist.y * dist.y));
}

static void inith_r_o(data_t *data, sfVector3f *r, sfVector2f *o, int *dof)
{
    float atan = -1 / tan(data->r->angle);

    if (data->r->angle > PI) {
        r->y = (((int)data->p->pos.y / MAP_S) * MAP_S) - 0.0001;
        r->x = (data->p->pos.y - r->y) * atan + data->p->pos.x;
        o->y = -MAP_S;
        o->x = -o->y * atan;
    }
    if (data->r->angle < PI) {
        r->y = (((int)data->p->pos.y / MAP_S) * MAP_S) + MAP_S;
        r->x = (data->p->pos.y - r->y) * atan + data->p->pos.x;
        o->y = MAP_S;
        o->x = -o->y * atan;
    }
    if (data->r->angle == 0 || (double)data->r->angle == (double)PI) {
        r->x = data->p->pos.x;
        r->y = data->p->pos.y;
        *dof = MAP_Y;
    }
}

sfVector3f check_h_lines(data_t *data)
{
    sfVector2f o = {0, 0};
    sfVector2i m = {0, 0};
    sfVector3f r = {0, 0, 100000};
    int dof = 0;

    inith_r_o(data, &r, &o, &dof);
    while (dof < MAP_Y) {
        m = (sfVector2i){(int) r.x / MAP_S, (int) r.y / MAP_S};
        if (m.x >= 0 && m.y >= 0 && m.y <= MAP_Y && m.x <= MAP_X &&
            data->map->map[m.y][m.x] > 0) {
            r.z = sqrt(distance(data->p->pos, r));
            dof = MAP_Y;
        } else {
            r = (sfVector3f){o.x + r.x, o.y + r.y, r.z};
            dof++;
        }
    }
    return r;
}

static void initv_r_o(data_t *data, sfVector3f *r, sfVector2f *o, int *dof)
{
    float ntan = -tan(data->r->angle);

    if (data->r->angle > P2 && data->r->angle < P3) {
        r->x = (((int)data->p->pos.x / MAP_S) * MAP_S) - 0.0001;
        r->y = (data->p->pos.x - r->x) * ntan + data->p->pos.y;
        o->x = -MAP_S;
        o->y = -o->x * ntan;
    }
    if (data->r->angle < P2 || data->r->angle > P3) {
        r->x = (((int)data->p->pos.x / MAP_S) * MAP_S) + MAP_S;
        r->y = (data->p->pos.x - r->x) * ntan + data->p->pos.y;
        o->x = MAP_S;
        o->y = -o->x * ntan;
    }
    if (data->r->angle == 0 || (double)data->r->angle == (double)PI) {
        r->x = data->p->pos.x;
        r->y = data->p->pos.y;
        *dof = MAP_X;
    }
}

sfVector3f check_v_lines(data_t *data)
{
    sfVector2f o = {0, 0};
    sfVector2i m = {0, 0};
    sfVector3f r = {0, 0, 100000};
    int dof = 0;

    initv_r_o(data, &r, &o, &dof);
    while (dof <= MAP_X) {
        m = (sfVector2i){(int) r.x / MAP_S, (int) r.y / MAP_S};
        if (m.x >= 0 && m.y >= 0 && m.y <= MAP_Y && m.x <= MAP_X &&
            data->map->map[m.y][m.x] > 0) {
            r.z = sqrt(distance(data->p->pos, r));
            dof = MAP_X + 1;
        } else {
            r = (sfVector3f){o.x + r.x, o.y + r.y, r.z};
            dof++;
        }
    }
    return r;
}
