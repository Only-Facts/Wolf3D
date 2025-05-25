/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** settings_events.c
*/

#include "struct.h"
#include "macro.h"
#include "my.h"
#include <stdio.h>

static void handle_click_events(data_t *data, sfEvent event)
{
    sfVector2i mouse_pos;

    if (event.type != sfEvtMouseButtonPressed ||
        event.mouseButton.button != sfMouseLeft)
        return;
    mouse_pos.x = event.mouseButton.x;
    mouse_pos.y = event.mouseButton.y;
    handle_fps_text_click(data, mouse_pos);
    handle_volume_text_click(data, mouse_pos);
}

void handle_settings_events(data_t *data)
{
    sfEvent event;

    if (!data || !data->win)
        return;
    while (sfRenderWindow_pollEvent(data->win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->win);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            data->scenes = MENU;
        handle_click_events(data, event);
    }
}
