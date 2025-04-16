/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** map.c
*/

#include "my.h"
#include "macro.h"

static void outline(data_t *data, size_t y, size_t x)
{
    if (y == 0 || y == MAP_Y - 1 || x == 0 || x == MAP_X - 1)
        data->map->map[y][x] = 1;
    else
        data->map->map[y][x] = 0;
}

static size_t empty_map(data_t *data)
{
    data->map->map = malloc(sizeof(int *) * MAP_Y);

    if (!data->map->map)
        return EXIT_ERROR;
    for (size_t y = 0; y < MAP_Y; y++) {
        data->map->map[y] = malloc(sizeof(int) * MAP_X);
        for (size_t x = 0; x < MAP_X; x++)
            outline(data, y, x);
    }
    return EXIT_SUCCESS;
}

size_t init_map(data_t *data)
{
    data->map = malloc(sizeof(map_t));

    if (!data->map || empty_map(data) == EXIT_ERROR)
        return EXIT_ERROR;
    data->map->map[1][2] = 1;
    data->map->map[2][2] = 1;
    data->map->map[3][2] = 1;
    data->map->map[5][5] = 1;
    return EXIT_SUCCESS;
}
