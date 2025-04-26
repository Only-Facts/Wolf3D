/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** map.c
*/

#include "my.h"
#include "macro.h"
#include <stdio.h>

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

static int **arr_to_map(char **arr)
{
    size_t map_size = get_array_len((const char **)arr);
    int **map = malloc(sizeof(int *) * map_size + 1);
    char c;

    if (!arr)
        return NULL;
    for (size_t i = 0; i < map_size; i++) {
        map[i] = malloc(sizeof(int) * get_len(arr[i]));
        for (size_t j = 0; arr[i][j]; j++) {
            c = arr[i][j];
            map[i][j] = atoi(&c);
            if (map[i][j] < 0)
                return NULL;
        }
    }
    free_arr(arr);
    return map;
}

static int ** file_to_map(const char *filepath)
{
    char *buffer = NULL;
    char **arr = NULL;
    int **map = NULL;

    if (!filepath)
        return NULL;
    buffer = read_file(filepath);\
    if (!buffer)
        return NULL;
    arr = cut(buffer, "\n");
    if (!arr)
        return NULL;
    map = arr_to_map(arr);
    return map;
}

size_t init_map(data_t *data)
{
    data->map = malloc(sizeof(map_t));
    if (!data->map)
        return EXIT_ERROR;
    data->map->map = file_to_map("assets/txt/map");
    for (int i = 0; data->map->map[i]; i++)
        for (int j = 0; data->map->map[i][j]; j++)
            printf("%i", data->map->map[i][j]);
    return EXIT_SUCCESS;
}
