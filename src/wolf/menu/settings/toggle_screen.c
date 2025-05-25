/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** toggle_screen
*/

#include "my.h"
#include <stdio.h>
#include <string.h>
#include "macro.h"

static char *mode_str(data_t *data, char str[])
{
    if (!data)
        return (char *){0};
    if (data->fullscreen == 1)
        strcpy(str, "Fullscreen");
    else
        strcpy(str, "Windowed");
    return str;
}

sfText *create_mode_text(data_t *data)
{
    sfText *text = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f, HEIGHT / 2.0f + 160};
    char mode_text[20];
    char str[14];

    if (!text || !font)
        return NULL;
    snprintf(mode_text, 20, "Mode: %s", mode_str(data, str));
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 60);
    sfText_setString(text, mode_text);
    sfText_setPosition(text, pos);
    sfText_setOrigin(text, (sfVector2f){
        sfText_getGlobalBounds(text).width / 2.0f,
        sfText_getGlobalBounds(text).height / 2.0f});
    sfText_setFillColor(text, WHITE);
    return text;
}

void update_mode_text(data_t *data)
{
    char mode_text[20];
    char str[14];

    if (!data || !data->ftext)
        return;
    snprintf(mode_text, 20, "Mode: %s", mode_str(data, str));
    sfText_setString(data->ftext, mode_text);
}
