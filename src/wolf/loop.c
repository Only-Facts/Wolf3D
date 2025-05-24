/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** scenes
*/

#include "my.h"
#include "macro.h"
#include <sys/time.h>

static double update_dtime(data_t *data, struct timeval *t1)
{
    struct timeval t2 = {0};
    double fps = 0;

    gettimeofday(&t2, NULL);
    data->dtime = (t2.tv_sec - t1->tv_sec) * 1000.0;
    data->dtime += (t2.tv_usec - t1->tv_usec) / 1000.0;
    fps = 1000.0 / data->dtime;
    return fps;
}

size_t loop(data_t *data)
{
    struct timeval t1 = {0};
    double fps = 0;

    while (sfRenderWindow_isOpen(data->win)){
        gettimeofday(&t1, NULL);
        sfRenderWindow_clear(data->win, GREY);
        if (scenes(data, fps) == EXIT_ERROR)
            return EXIT_ERROR;
        sfRenderWindow_display(data->win);
        fps = update_dtime(data, &t1);
    }
    return EXIT_SUCCESS;
}
