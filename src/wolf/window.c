/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** window
*/

#include "my.h"
#include "macro.h"

void change_screen_mode(data_t *data)
{
    sfVideoMode mode = {0};

    sfRenderWindow_destroy(data->win);
    if (data->fullscreen) {
        mode = (sfVideoMode){WIDTH, HEIGHT, 32};
        data->win = sfRenderWindow_create(mode, TITLE, sfClose, NULL);
        data->fullscreen = 0;
    } else {
        mode = sfVideoMode_getDesktopMode();
        data->win = sfRenderWindow_create(mode, TITLE, sfFullscreen, NULL);
        data->fullscreen = 1;
    }
    update_mode_text(data);
}

size_t init_window(data_t *data)
{
    sfVideoMode mode = {WIDTH, HEIGHT, 32};

    data->win = sfRenderWindow_create(mode, TITLE, sfFullscreen, NULL);
    data->fullscreen = 1;
    if (!data->win)
        return EXIT_ERROR;
    sfRenderWindow_setFramerateLimit(data->win, 60);
    return EXIT_SUCCESS;
}
