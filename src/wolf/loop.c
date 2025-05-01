/*
** EPITECH PROJECT, 2025
** wolf
** File description:
** scenes
*/

#include "my.h"
#include "macro.h"
#include <sys/time.h>

static void update_dtime(data_t *data, struct timeval *t1)
{
    struct timeval t2 = {0};

    gettimeofday(&t2, NULL);
    data->dtime = (t2.tv_sec - t1->tv_sec) * 1000.0;
    data->dtime += (t2.tv_usec - t1->tv_usec) / 1000.0;
    data->dtime /= 30.0;
}

size_t loop(data_t *data)
{
    struct timeval t1 = {0};

    while (sfRenderWindow_isOpen(data->win)){
        gettimeofday(&t1, NULL);
        sfRenderWindow_clear(data->win, GREY);
        event(data);
        draw(data);
        sfRenderWindow_display(data->win);
        update_dtime(data, &t1);
    }
    return EXIT_SUCCESS;
}
