/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** fire_shot
*/

#include "my.h"
#include <SFML/Config.h>
#include <SFML/Graphics/Vertex.h>
#include <SFML/System/Clock.h>
#include <SFML/System/Vector2.h>
#include "math.h"
#include "struct.h"


static void handle_point(data_t *data, sfVector2f s, sfUint8 alpha, sfVertexArray *va)
{
    sfVertex v;

    if (!data)
        return;
    v.position = (sfVector2f){s.x, s.y};
    v.color = sfColor_fromRGBA(255, 140 + rand() % 100, 0, alpha);
    sfVertexArray_append(va, v);
}

static part_t *update_point(data_t *data, float dt, part_t *p)
{
    if (!data)
        return NULL;
    p->x += p->vx * dt;
    p->y += p->vy * dt;
    p->z += p->vz * dt;
    p->time -= dt;
    return p;
}

static void init_point_upt(data_t *data, float scale, float dt, sfVertexArray *va)
{
    sfVector2f c = {0, 0};
    sfVector2f d = {0, 0};
    sfVector2f s = {0, 0};
    sfUint8 alpha;
    for (size_t i = 0; i < data->part->part_count;) {
        part_t* p = &data->part[i];
        p = update_point(data, dt, p);
        d.x = (p->x / p->z) * scale;
        d.y = (p->y / p->z) * scale;
        s.x = c.x + d.x;
        s.y = c.y + d.y;
        alpha = (sfUint8)(255.0f * (p->time));
        if (p->z > 30.0f || p->time <= 0.0f) {
            data->part[i] = data->part[--data->part->part_count];
            continue;
        }
        handle_point(data, s, alpha, va);
        i++;
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

static void init_f_burst(data_t *data)
{
    if (!data)
        return;
    data->part[0].part_count = 0;
    for (int i = 0; i < 50 && data->part->part_count < 500; ++i) {
        data->part->angle = ((float)rand() / RAND_MAX) * 2.0f * 3.1415f;
        data->part->spread = ((float)rand() / RAND_MAX) * 0.5f;
        data->part->speed = 4.0f + ((float)rand() / RAND_MAX) * 2.0f;
            data->part[data->part[0].part_count++] = (part_t){
                .x = 0, .y = 0, .z = 1.0f,
                .vx = cos(data->part->angle) * data->part->spread,
                .vy = sin(data->part->angle) * data->part->spread,
                .vz = data->part->speed,
                .time = 1.5f
            };
    }
}

void fire_shot(data_t *data)
{
    float dt = 0.0;

    if (!data)
        return;
    sfClock *clock = sfClock_create();
    data->part[500];
    init_f_burst(data);
    dt = sfTime_asSeconds(sfClock_restart(clock));
    part_pos(data, dt);
    sfClock_destroy(clock);
}
