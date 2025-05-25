/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** settings.c
*/

#include "my.h"
#include "struct.h"
#include "macro.h"
#include <stdio.h>

static void toggle_volume_level(data_t *data)
{
    if (!data || !data->menu)
        return;
    data->menu->volume_level += 10;
    if (data->menu->volume_level > 100)
        data->menu->volume_level = 0;
    update_volume_text(data->menu);
    update_music_volume(data);
}

static sfBool is_text_clicked(sfText *text, sfVector2i mouse_pos,
    sfRenderWindow *win)
{
    sfFloatRect bounds;
    sfVector2f world_pos;

    if (!text || !win)
        return sfFalse;
    bounds = sfText_getGlobalBounds(text);
    world_pos = sfRenderWindow_mapPixelToCoords(win, mouse_pos, NULL);
    return (world_pos.x >= bounds.left &&
            world_pos.x <= bounds.left + bounds.width &&
            world_pos.y >= bounds.top &&
            world_pos.y <= bounds.top + bounds.height);
}

static void init_settings_elements(data_t *data)
{
    if (!data || !data->menu)
        return;
    if (data->menu->fps_limit == 0)
        data->menu->fps_limit = 60;
    if (data->menu->fps_text == NULL)
        data->menu->fps_text = create_fps_text(data->menu->fps_limit);
    if (data->menu->volume_text == NULL)
        data->menu->volume_text = create_volume_text(data->menu->volume_level);
    if (data->ftext == NULL)
        data->ftext = create_mode_text(data);
}

void handle_fps_text_click(data_t *data, sfVector2i mouse_pos)
{
    if (!data || !data->menu || !data->menu->fps_text)
        return;
    if (is_text_clicked(data->menu->fps_text, mouse_pos, data->win))
        toggle_fps_limit(data);
}

void handle_volume_text_click(data_t *data, sfVector2i mouse_pos)
{
    if (!data || !data->menu || !data->menu->volume_text)
        return;
    if (is_text_clicked(data->menu->volume_text, mouse_pos, data->win))
        toggle_volume_level(data);
    if (is_text_clicked(data->ftext, mouse_pos, data->win))
        change_screen_mode(data);
}

static void draw_title_settings(sfRenderWindow *win)
{
    sfText *title = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f - 100, HEIGHT / 2.0f - 200};

    if (!title || !font)
        return;
    sfText_setFont(title, font);
    sfText_setCharacterSize(title, 72);
    sfText_setString(title, "SETTINGS");
    sfText_setPosition(title, pos);
    sfText_setFillColor(title, WHITE);
    sfRenderWindow_drawText(win, title, NULL);
    sfFont_destroy(font);
    sfText_destroy(title);
}

static void handle_text_hover(sfText *text, sfVector2f world_pos)
{
    sfFloatRect bounds;

    if (!text)
        return;
    bounds = sfText_getGlobalBounds(text);
    if (world_pos.x >= bounds.left && world_pos.x <=
        bounds.left + bounds.width &&
        world_pos.y >= bounds.top && world_pos.y <=
        bounds.top + bounds.height)
        sfText_setFillColor(text, sfColor_fromRGB(180, 20, 30));
    else
        sfText_setFillColor(text, WHITE);
}

static void handle_settings_hover(data_t *data)
{
    sfVector2i mouse_pos;
    sfVector2f world_pos;

    if (!data || !data->menu || !data->win)
        return;
    mouse_pos = sfMouse_getPositionRenderWindow(data->win);
    world_pos = sfRenderWindow_mapPixelToCoords(data->win, mouse_pos, NULL);
    handle_text_hover(data->menu->fps_text, world_pos);
    handle_text_hover(data->menu->volume_text, world_pos);
    handle_text_hover(data->ftext, world_pos);
}

static void draw_settings(data_t *data)
{
    if (!data || !data->win || !data->menu)
        return;
    draw_background(data->win);
    draw_title_settings(data->win);
    handle_settings_hover(data);
    if (data->menu->fps_text)
        sfRenderWindow_drawText(data->win, data->menu->fps_text, NULL);
    if (data->menu->volume_text)
        sfRenderWindow_drawText(data->win, data->menu->volume_text, NULL);
    if (data->ftext)
        sfRenderWindow_drawText(data->win, data->ftext, NULL);
}

size_t display_settings(data_t *data)
{
    if (!data || !data->win)
        return EXIT_ERROR;
    if (data->menu == NULL) {
        data->scenes = MENU;
        return EXIT_SUCCESS;
    }
    init_settings_elements(data);
    handle_settings_events(data);
    draw_settings(data);
    return EXIT_SUCCESS;
}
