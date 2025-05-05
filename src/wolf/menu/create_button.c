/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** create_button.c
*/

#include "my.h"
#include "struct.h"
#include "macro.h"
#include <stdio.h>

sfTexture *load_button_texture(const char *path)
{
    return sfTexture_createFromFile(path, NULL);
}

sfSprite *init_button_sprite(sfTexture *texture, sfVector2f pos)
{
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    return sprite;
}

button_t *create_button(const char *path, sfVector2f pos)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->position = pos;
    button->sprite = NULL;
    button->texture = NULL;
    button->texture = load_button_texture(path);
    if (!button->texture) {
        free(button);
        return NULL;
    }
    button->sprite = init_button_sprite(button->texture, pos);
    if (!button->sprite) {
        sfTexture_destroy(button->texture);
        free(button);
        return NULL;
    }
    return button;
}

void destroy_button(button_t *button)
{
    if (!button)
        return;
    if (button->sprite)
        sfSprite_destroy(button->sprite);
    if (button->texture)
        sfTexture_destroy(button->texture);
    free(button);
}

void draw_title(sfRenderWindow *win)
{
    sfText *title = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2 - 100, HEIGHT / 2 - 200};

    if (!title || !font)
        return;
    sfText_setFont(title, font);
    sfText_setCharacterSize(title, 48);
    sfText_setString(title, "WOLF3D");
    sfText_setPosition(title, pos);
    sfText_setFillColor(title, WHITE);
    sfRenderWindow_drawText(win, title, NULL);
    sfText_destroy(title);
}
