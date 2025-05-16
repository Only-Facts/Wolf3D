/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** settings.c
*/

#include "my.h"
#include "struct.h"
#include "macro.h"

static void handle_settings_events(data_t *data, menu_t *menu)
{
    sfEvent event;

    if (!data || !menu || !data->win)
        return;
    while (sfRenderWindow_pollEvent(data->win, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(data->win);
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            data->scenes = MENU;
    }
}

static void update_settings_animations(menu_t *menu, float dtime)
{
    if (!menu)
        return;
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

static void draw_settings(sfRenderWindow *win, menu_t *menu)
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
    if (data->menu == NULL) {
        data->scenes = MENU;
        return EXIT_SUCCESS;
    }
    handle_settings_events(data, data->menu);
    update_settings_animations(data->menu, data->dtime);
    draw_settings(data->win, data->menu);
    return EXIT_SUCCESS;
}
