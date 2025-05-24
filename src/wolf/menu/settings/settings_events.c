/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** settings_events.c
*/

#include "struct.h"
#include "macro.h"
#include "my.h"

void handle_settings_events(data_t *data)
{
    sfEvent event;
    sfVector2i mouse_pos;

    if (!data || !data->win)
        return;
    while (sfRenderWindow_pollEvent(data->win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->win);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyF11)
            change_screen_mode(data);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            data->scenes = MENU;
        if (event.type == sfEvtMouseButtonPressed &&
            event.mouseButton.button == sfMouseLeft) {
            mouse_pos.x = event.mouseButton.x;
            mouse_pos.y = event.mouseButton.y;
            handle_fps_text_click(data, mouse_pos);
        }
    }
}

void draw_background_settings(sfRenderWindow *win)
{
    sfRectangleShape *bg = sfRectangleShape_create();

    if (!bg)
        return;
    sfRectangleShape_setSize(bg, (sfVector2f){WIDTH, HEIGHT});
    sfRectangleShape_setFillColor(bg, GREY);
    sfRenderWindow_drawRectangleShape(win, bg, NULL);
    sfRectangleShape_destroy(bg);
}
