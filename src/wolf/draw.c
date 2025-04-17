/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** draw.c
*/

#include "my.h"
#include "macro.h"
#include <stdio.h>
#include <math.h>

static sfVertexArray *create_line(sfVector2f a, sfVector2f b)
{
    sfVertexArray *va = sfVertexArray_create();
    sfVertex v1 = {.position = a, .color = WHITE};
    sfVertex v2 = {.position = b, .color = WHITE};

    sfVertexArray_append(va, v1);
    sfVertexArray_append(va, v2);
    sfVertexArray_setPrimitiveType(va, sfLinesStrip);
    return va;
}

static void create_wall(data_t *data, sfColor color, sfVector2f line, int i)
{
    sfRectangleShape *wall = sfRectangleShape_create();

    if (!wall)
        return;
    sfRectangleShape_setPosition(wall, (sfVector2f){i * 8 + 250, line.y});
    sfRectangleShape_setSize(wall, (sfVector2f){8, line.x});
    sfRectangleShape_setFillColor(wall, color);
    sfRenderWindow_drawRectangleShape(data->win, wall, NULL);
    sfRectangleShape_destroy(wall);
}

static void draw_walls(data_t *data, sfColor color, float dist, size_t i)
{
    sfVector2f line = {0, 0};
    float ca = data->p->angle - data->r->angle;

    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    dist *= cos(ca);
    line.x = (MAP_S * 320) / dist;
    if (line.x > 320)
        line.x = 320;
    line.y = 260 - line.x / 2;
    create_wall(data, color, line, i);
}

static void draw_varray(data_t *data, float *dist, sfColor *color)
{
    sfVertexArray *ray = NULL;
    sfVector3f v = {0, 0, 0};
    sfVector3f h = {0, 0, 0};

    v = check_v_lines(data);
    h = check_h_lines(data);
    if (v.z < h.z) {
        ray = create_line(data->p->pos, (sfVector2f){v.x, v.y});
        *dist = v.z;
    } else {
        ray = create_line(data->p->pos, (sfVector2f){h.x, h.y});
        *dist = h.z;
        color->b -= 20;
    }
    sfRenderWindow_drawVertexArray(data->win, ray, NULL);
    sfVertexArray_destroy(ray);
}

static void draw_rays(data_t *data)
{
    float dist = 0;
    sfColor color = WHITE;

    data->r->angle = data->p->angle - RAD * 45;
    for (size_t i = 0; i < 90; i++) {
        if (data->r->angle < 0)
            data->r->angle += 2 * PI;
        if (data->r->angle > 2 * PI)
            data->r->angle -= 2 * PI;
        draw_varray(data, &dist, &color);
        draw_walls(data, color, dist, i);
        data->r->angle += RAD;
        color = WHITE;
    }
}

static void draw_player(data_t *data)
{
    sfVector2f pos = {data->p->pos.x - 3, data->p->pos.y - 3};

    sfRectangleShape_setPosition(data->p->texture, pos);
    sfRenderWindow_drawRectangleShape(data->win, data->p->texture, NULL);
    draw_rays(data);
}

static void draw_map(data_t *data)
{
    sfRectangleShape *tile = {0};
    sfColor colors[2] = {BLACK, sfColor_fromRGB(100, 100, 200)};

    for (size_t y = 0; y < MAP_Y; y++)
        for (size_t x = 0; x < MAP_X; x++) {
            tile = sfRectangleShape_create();
            sfRectangleShape_setFillColor(tile, colors[data->map->map[y][x]]);
            sfRectangleShape_setSize(tile, (sfVector2f){MAP_S - 1, MAP_S - 1});
            sfRectangleShape_setPosition(tile,
                (sfVector2f){x * MAP_S, y * MAP_S});
            sfRenderWindow_drawRectangleShape(data->win, tile, NULL);
        }
}

void draw(data_t *data)
{
    draw_map(data);
    draw_player(data);
}
