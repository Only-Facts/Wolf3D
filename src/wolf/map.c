/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** map.c
*/

#include "my.h"
#include "struct.h"
#include <stdio.h>

static size_t add_to_map(data_t *data, const size_t i, const char **arr)
{
    char c = 0;

    for (size_t j = 0; arr[i][j] != '\0'; j++) {
        c = arr[i][j];
        data->map->map[i][j] = atoi(&c);
        if (data->map->map[i][j] < 0)
            return EXIT_ERROR;
    }
    return EXIT_SUCCESS;
}

static size_t arr_to_map(data_t *data, char **arr)
{
    size_t map_size = get_array_len((const char **)arr);

    if (!arr)
        return EXIT_ERROR;
    data->map->map = malloc(sizeof(int *) * (map_size + 1));
    for (size_t i = 0; i < map_size; i++) {
        data->map->map[i] = malloc(sizeof(int) * (get_len(arr[i]) + 1));
        if (add_to_map(data, i, (const char **)arr) == EXIT_ERROR)
            return EXIT_ERROR;
    }
    free_arr(arr);
    return EXIT_SUCCESS;
}

static size_t file_to_map(data_t *data, const char *filepath)
{
    char *buffer = NULL;
    char **arr = NULL;
    size_t exit = 0;

    if (!filepath)
        return EXIT_ERROR;
    buffer = read_file(filepath);
    if (!buffer)
        return EXIT_ERROR;
    arr = cut(buffer, "\n");
    if (!arr)
        return EXIT_ERROR;
    exit = arr_to_map(data, arr);
    free(buffer);
    return exit;
}

size_t init_map(data_t *data)
{
    data->map = malloc(sizeof(map_t));
    if (!data->map || file_to_map(data, "assets/txt/map") != EXIT_SUCCESS)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}
