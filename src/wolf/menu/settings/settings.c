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

static sfText *create_fps_text(int fps_limit)
{
    sfText *text = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f, HEIGHT / 2.0f};
    char fps_text[20];

    if (!text || !font)
        return NULL;
    snprintf(fps_text, 20, "FPS Limit: %d", fps_limit);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 60);
    sfText_setString(text, fps_text);
    sfText_setPosition(text, pos);
    sfText_setOrigin(text, (sfVector2f){
        sfText_getGlobalBounds(text).width / 2.0f,
        sfText_getGlobalBounds(text).height / 2.0f});
    sfText_setFillColor(text, WHITE);
    return text;
}

static void update_fps_text(menu_t *menu)
{
    char fps_text[20];

    if (!menu || !menu->fps_text)
        return;
    snprintf(fps_text, 20, "FPS Limit: %d", menu->fps_limit);
    sfText_setString(menu->fps_text, fps_text);
}

static void toggle_fps_limit(data_t *data)
{
    int new_limit = 0;

    if (!data || !data->menu)
        return;
    if (data->menu->fps_limit == 30)
        new_limit = 60;
    else if (data->menu->fps_limit == 60)
        new_limit = 120;
    else
        new_limit = 30;
    data->menu->fps_limit = new_limit;
    sfRenderWindow_setFramerateLimit(data->win, new_limit);
    update_fps_text(data->menu);
}

static sfBool is_fps_text_clicked(sfText *text, sfVector2i mouse_pos,
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
}

void handle_fps_text_click(data_t *data, sfVector2i mouse_pos)
{
    if (!data || !data->menu || !data->menu->fps_text)
        return;
    if (is_fps_text_clicked(data->menu->fps_text, mouse_pos, data->win))
        toggle_fps_limit(data);
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

static void handle_fps_text_hover(data_t *data, sfVector2i mouse_pos)
{
    sfText *text = data->menu->fps_text;
    sfFloatRect bounds;
    sfVector2f world_pos;

    if (!data || !data->menu || !text || !data->win)
        return;
    bounds = sfText_getGlobalBounds(text);
    world_pos = sfRenderWindow_mapPixelToCoords(data->win, mouse_pos, NULL);
    if (world_pos.x >= bounds.left && world_pos.x <=
        bounds.left + bounds.width &&
        world_pos.y >= bounds.top && world_pos.y <=
        bounds.top + bounds.height)
        sfText_setFillColor(text, sfColor_fromRGB(180, 20, 30));
    else
        sfText_setFillColor(text, WHITE);
}

static void draw_settings(data_t *data)
{
    sfVector2i mouse_pos;

    if (!data || !data->win || !data->menu)
        return;
    draw_background(data->win);
    draw_title_settings(data->win);
    mouse_pos = sfMouse_getPositionRenderWindow(data->win);
    handle_fps_text_hover(data, mouse_pos);
    if (data->menu->fps_text)
        sfRenderWindow_drawText(data->win, data->menu->fps_text, NULL);
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
