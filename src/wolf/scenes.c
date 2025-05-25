/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** scenes
*/

#include "my.h"
#include "struct.h"

static size_t game_scene(data_t *data, double fps)
{
    if (!data)
        return EXIT_ERROR;
    event(data);
    draw(data);
    draw_fps(data->win, fps);
    weapon(data);
    return EXIT_SUCCESS;
}

static size_t settings_scene(data_t *data)
{
    if (!data)
        return EXIT_ERROR;
    if (display_settings(data) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

static size_t menu_scene(data_t *data)
{
    if (!data)
        return EXIT_ERROR;
    if (display_menu(data) == EXIT_ERROR)
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

size_t scenes(data_t *data, const double fps)
{
    if (!data)
        return EXIT_ERROR;
    update_music(data);
    if (data->scenes == MENU)
        menu_scene(data);
    if (data->scenes == GAME)
        game_scene(data, fps);
    if (data->scenes == PAUSE)
        menu_scene(data);
    if (data->scenes == SETTINGS)
        settings_scene(data);
    return EXIT_SUCCESS;
}
