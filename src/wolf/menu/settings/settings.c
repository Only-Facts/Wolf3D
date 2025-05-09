/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** settings.c
*/

#include "my.h"
#include "struct.h"
#include "macro.h"

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

static void draw_title_settings(sfRenderWindow *win)
{
    sfText *title = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f - 100, HEIGHT / 2.0f - 200};

    if (!title || !font)
        return;
    sfText_setFont(title, font);
    sfText_setCharacterSize(title, 48);
    sfText_setString(title, "SETTINGS");
    sfText_setPosition(title, pos);
    sfText_setFillColor(title, WHITE);
    sfRenderWindow_drawText(win, title, NULL);
    sfText_destroy(title);
}


static void draw_menu(sfRenderWindow *win, menu_t *menu)
{
    if (!win || !menu)
        return;
    draw_background_settings(win);
    draw_title_settings(win);
}

size_t display_settings(data_t *data)
{
    if (!data || !data->win)
        return EXIT_ERROR;
    handle_menu_events(data);
    draw_menu(data->win, data->menu);
    return EXIT_SUCCESS;
}
