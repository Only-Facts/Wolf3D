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

static size_t flashlight(data_t *data, sfVector2i i, sfVector2f line)
{
    if (data->flash < 0)
        return EXIT_SUCCESS;
    if (i.x > 30 && i.x < 60 &&
        line.x / 5 < i.y && line.x * 4 / 5 > i.y)
            return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

static void create_rectangle(data_t *data, sfColor color,
    sfVector2i i, sfVector2f line)
{
    sfRectangleShape *wall = sfRectangleShape_create();
    size_t start = (WIDTH / 2) - ((data->FOV * MAP_S) / 2);

    if (!wall)
        return;
    sfRectangleShape_setPosition(wall, (sfVector2f){i.x * MAP_S + start,
        i.y * 1.5 + line.y});
    sfRectangleShape_setSize(wall, (sfVector2f){MAP_S, MAP_S});
    if (flashlight(data, i, line))
        color = sfColor_add(color, (sfColor){40, 40, 40, 0};
    sfRectangleShape_setFillColor(wall, color);
    sfRenderWindow_drawRectangleShape(data->win, wall, NULL);
    sfRectangleShape_destroy(wall);
}

static void create_wall(data_t *data, sfVector3f ty, sfVector2f line, int i)
{
    sfColor color = {0};
    sfVector2f t = {0, ty.y * ty.x};

    if (ty.z) {
        t.x = (int)(data->r->r.x / 2.0) % 32;
        if (data->r->angle > 180)
            t.x = 31 - t.x;
    } else {
        t.x = (int)(data->r->r.y / 2.0) % 32;
        if (data->r->angle > 90 && data->r->angle < 270)
            t.x = 31 - t.x;
    }
    for (size_t y = 0; y < line.x; y++) {
        color = data->img->wall_arr[(int)t.y * 32 + (int)t.x];
        create_rectangle(data, color, (sfVector2i){i, y}, line);
        t.y += ty.x;
    }
}

static void draw_walls(data_t *data, int shade, size_t i)
{
    sfVector2f line = {0, 0};
    float ca = (data->p->angle - data->r->angle);
    sfVector3f ty = {0, 0, shade};

    if (ca < 0)
        ca += 2 * PI;
    if (ca > 2 * PI)
        ca -= 2 * PI;
    data->r->dist *= cos(ca);
    line.x = (MAP_S * 320) / data->r->dist;
    ty.x = 32.0 / (float)line.x;
    if (line.x > 320) {
        ty.y = (line.x - 320) / 2.0;
        line.x = 320;
    }
    line.y = 500 - line.x / 1.5;
    create_wall(data, ty, line, i);
}

static void draw_varray(data_t *data, int *shade)
{
    sfVertexArray *ray = NULL;
    sfVector3f v = {0, 0, 0};
    sfVector3f h = {0, 0, 0};

    v = check_v_lines(data);
    h = check_h_lines(data);
    if (v.z < h.z) {
        ray = create_line(data->p->pos, (sfVector2f){v.x, v.y});
        data->r->dist = v.z;
        data->r->r = (sfVector2f){v.x, v.y};
        *shade = 0;
    } else {
        ray = create_line(data->p->pos, (sfVector2f){h.x, h.y});
        data->r->dist = h.z;
        data->r->r = (sfVector2f){h.x, h.y};
        *shade = 1;
    }
    sfRenderWindow_drawVertexArray(data->win, ray, NULL);
    sfVertexArray_destroy(ray);
}

static void draw_rays(data_t *data)
{
    int shade = 0;

    data->r->angle = data->p->angle - RAD * (data->FOV / 2);
    for (size_t i = 0; i < data->FOV; i++) {
        if (data->r->angle < 0)
            data->r->angle += 2 * PI;
        if (data->r->angle > 2 * PI)
            data->r->angle -= 2 * PI;
        draw_varray(data, &shade);
        draw_walls(data, shade, i);
        data->r->angle += RAD;
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
    sfColor colors[2] = {GREY, sfColor_fromRGB(125, 88, 79)};

    for (size_t y = 0; y < MAP_Y; y++)
        for (size_t x = 0; x < MAP_X; x++) {
            tile = sfRectangleShape_create();
            sfRectangleShape_setFillColor(tile, colors[data->map->map[y][x]]);
            sfRectangleShape_setSize(tile, (sfVector2f){MAP_S - 1, MAP_S - 1});
            sfRectangleShape_setPosition(tile,
                (sfVector2f){x * MAP_S, y * MAP_S});
            sfRenderWindow_drawRectangleShape(data->win, tile, NULL);
            sfRectangleShape_destroy(tile);
        }
}

static void draw_outline(data_t *data)
{
    sfRectangleShape *outline = sfRectangleShape_create();
    sfColor color = sfColor_fromRGB(46, 46, 46);

    if (!outline)
        return;
    sfRectangleShape_setFillColor(outline, color);
    sfRectangleShape_setSize(outline,
        (sfVector2f){data->FOV * MAP_S + 20, 510});
    sfRectangleShape_setPosition(outline,
        (sfVector2f){(WIDTH / 2) - (data->FOV * MAP_S) / 2 - 10, 280});
    sfRenderWindow_drawRectangleShape(data->win, outline, NULL);
    sfRectangleShape_destroy(outline);
}

void draw(data_t *data)
{
    draw_outline(data);
    draw_floor(data);
    draw_ceiling(data);
    draw_map(data);
    draw_player(data);
    if (data->e->is_alive)
        sfRenderWindow_drawRectangleShape(data->win, data->e->dot, NULL);
}
