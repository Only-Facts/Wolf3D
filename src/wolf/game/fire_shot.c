/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** fire_shot
*/

#include "my.h"
#include <SFML/Config.h>
#include <stdlib.h>
#include "math.h"
#include "struct.h"
#include "macro.h"
#include <time.h>
#include <stdio.h>

static void handle_point(data_t *data, sfVector2f s, sfVertexArray *va)
{
    sfVertex v;

    if (!data)
        return;
    v.position = (sfVector2f){s.x, s.y};
    v.color = sfColor_fromRGB(255, 140 + rand() % 100, 0);
    sfVertexArray_append(va, v);
}

static part_t *update_point(data_t *data, float dt, part_t *p, size_t i)
{
    if (!data)
        return NULL;
    p = &data->part[i];
    p->x += p->vx * dt;
    p->y += p->vy * dt;
    p->z += p->vz * dt * 3;
    p->time -= dt;
    return p;
}

static void init_point_upt(data_t *data, float scale, float dt,
    sfVertexArray *va)
{
    sfVector2f c = {WIDTH / 2.0, HEIGHT / 2.0};
    sfVector2f d = {0, 0};
    sfVector2f s = {0, 0};
    part_t *p = NULL;

    for (size_t i = 0; i < data->part_count;) {
        p = update_point(data, dt, p, i);
        d.x = (p->x / p->z) * scale;
        d.y = (p->y / p->z) * scale;
        s.x = c.x + d.x;
        s.y = c.y + d.y;
        printf("%.2f", p->z);
        if (p->z > 1000.0f) {
            data->part_count--;
            data->part[i] = data->part[data->part_count];
            continue;
        }
        handle_point(data, s, va);
        ++i;
    }
}

static void part_pos(data_t *data, float dt)
{
    float scale = 500.0;
    sfVertexArray* va = sfVertexArray_create();

    if (!data)
        return;
    sfVertexArray_setPrimitiveType(va, sfPoints);
    init_point_upt(data, scale, dt, va);
    sfRenderWindow_drawVertexArray(data->win, va, NULL);
    sfVertexArray_destroy(va);
}

void init_f_burst(data_t *data)
{
    if (!data || !data->part)
        return;
    data->part_count = 0;
    for (int i = 0; i < 50 && data->part_count < 500; ++i) {
        data->part[data->part_count] = (part_t) {
            .x = 0, .y = 0, .z = 1.0f,
            .vx = cosf(((float)rand() / RAND_MAX) * 2.0f * 3.1415f) *
            ((float)rand() / RAND_MAX) * 0.5f,
            .vy = sinf(((float)rand() / RAND_MAX) * 2.0f * 3.1415f) *
            ((float)rand() / RAND_MAX) * 0.5f,
            .vz = 4.0f + ((float)rand() / RAND_MAX) * 2.0f,
            .time = 1.5f
        };
        data->part_count++;
    }
}

void fire_shot(data_t *data)
{
    if (!data)
        return;
    part_pos(data, data->dtime);
}
