/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** create_menu.c
*/

#include "my.h"
#include "macro.h"
#include "struct.h"

static void configure_menu_button(sfText *button, sfFont *font,
    const char *label, sfVector2f position)
{
    sfText_setFont(button, font);
    sfText_setCharacterSize(button, 42);
    sfText_setString(button, label);
    sfText_setPosition(button, position);
    sfText_setOrigin(button, (sfVector2f){
        sfText_getGlobalBounds(button).width / 2.0f,
        sfText_getGlobalBounds(button).height / 2.0f});
    sfText_setFillColor(button, WHITE);
}

static void init_menu_buttons(menu_t *menu, sfFont *font)
{
    sfVector2f pos_play = {WIDTH / 2.0f, HEIGHT / 2.0f + 100};
    sfVector2f pos_options = {WIDTH / 2.0f, HEIGHT / 2.0f + 160};
    sfVector2f pos_quit = {WIDTH / 2.0f, HEIGHT / 2.0f + 220};

    menu->play = sfText_create();
    menu->options = sfText_create();
    menu->quit = sfText_create();
    configure_menu_button(menu->play, font, "PLAY", pos_play);
    configure_menu_button(menu->options, font, "OPTIONS", pos_options);
    configure_menu_button(menu->quit, font, "QUIT", pos_quit);
}

menu_t *create_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfFont *font = FONT;

    if (!menu || !font)
        return NULL;
    init_menu_buttons(menu, font);
    menu->fps_text = NULL;
    menu->background = NULL;
    menu->bg_texture = NULL;
    menu->fps_limit = 60;
    return menu;
}

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

void destroy_menu(menu_t *menu)
{
    if (!menu)
        return;
    if (menu->play)
        sfText_destroy(menu->play);
    if (menu->options)
        sfText_destroy(menu->options);
    if (menu->quit)
        sfText_destroy(menu->quit);
    if (menu->fps_text)
        sfText_destroy(menu->fps_text);
    if (menu->background)
        sfSprite_destroy(menu->background);
    if (menu->bg_texture)
        sfTexture_destroy(menu->bg_texture);
    free(menu);
}
