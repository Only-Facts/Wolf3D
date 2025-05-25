/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** fps_settings.c
*/

#include "my.h"
#include "macro.h"
#include "struct.h"
#include <stdio.h>

sfText *create_fps_text(int fps_limit)
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

sfText *create_volume_text(int volume_level)
{
    sfText *text = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f, HEIGHT / 2.0f + 80};
    char volume_text[20];

    if (!text || !font)
        return NULL;
    snprintf(volume_text, 20, "Volume: %d%%", volume_level);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 60);
    sfText_setString(text, volume_text);
    sfText_setPosition(text, pos);
    sfText_setOrigin(text, (sfVector2f){
        sfText_getGlobalBounds(text).width / 2.0f,
        sfText_getGlobalBounds(text).height / 2.0f});
    sfText_setFillColor(text, WHITE);
    return text;
}

void update_fps_text(menu_t *menu)
{
    char fps_text[20];

    if (!menu || !menu->fps_text)
        return;
    snprintf(fps_text, 20, "FPS Limit: %d", menu->fps_limit);
    sfText_setString(menu->fps_text, fps_text);
}

void update_volume_text(menu_t *menu)
{
    char volume_text[20];

    if (!menu || !menu->volume_text)
        return;
    snprintf(volume_text, 20, "Volume: %d%%", menu->volume_level);
    sfText_setString(menu->volume_text, volume_text);
}

void toggle_fps_limit(data_t *data)
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
