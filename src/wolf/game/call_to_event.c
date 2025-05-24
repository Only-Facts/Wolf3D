/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** call_to_event
*/

#include "my.h"

void call_to_event(data_t *data, sfEvent event)
{
    static size_t status = 0;

    if (!data)
        return;
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(data->win);
    if (sfKeyboard_isKeyPressed(sfKeyEscape))
        data->scenes = PAUSE;
    if (sfKeyboard_isKeyPressed(sfKeyL) && !status) {
        data->flash *= -1;
        status = 1;
    }
    if (event.type == sfEvtKeyReleased)
        status = 0;
}
