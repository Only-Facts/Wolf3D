/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** create_button.c
*/

#include "my.h"
#include "macro.h"

void draw_background(sfRenderWindow *win)
{
    sfSprite *s = sfSprite_create();
    sfTexture *bg = NULL;

    if (!s)
        return;
    bg = sfTexture_createFromFile("assets/img/background.png", NULL);
    if (!bg)
        return;
    sfSprite_setTexture(s, bg, sfTrue);
    sfSprite_setScale(s, (sfVector2f){1, 1});
    sfRenderWindow_drawSprite(win, s, NULL);
    sfTexture_destroy(bg);
    sfSprite_destroy(s);
}

sfSprite *init_button_sprite(sfTexture *texture, sfVector2f pos)
{
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setOrigin(sprite, (sfVector2f){
        sfTexture_getSize(texture).x / 2.0f,
        sfTexture_getSize(texture).y / 2.0f
    });
    sfSprite_setScale(sprite, (sfVector2f){1.0f, 1.0f});
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
    button->texture = sfTexture_createFromFile(path, NULL);
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
    button->anim = create_button_anim();
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
    if (button->anim)
        destroy_button_anim(button->anim);
    free(button);
}

void draw_title(sfRenderWindow *win)
{
    sfText *title = sfText_create();
    sfFont *font = FONT;
    sfVector2f pos = {WIDTH / 2.0f - 200, HEIGHT / 2.0f - 200};

    if (!title || !font)
        return;
    sfText_setFont(title, font);
    sfText_setCharacterSize(title, 72);
    sfText_setString(title, "Wolfenstein 3D");
    sfText_setPosition(title, pos);
    sfText_setFillColor(title, WHITE);
    sfRenderWindow_drawText(win, title, NULL);
    sfFont_destroy(font);
    sfText_destroy(title);
}
