/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** menu.c
*/

#include "my.h"
#include "macro.h"
#include "struct.h"
#include <SFML/Graphics/RenderWindow.h>

static void draw_background(sfRenderWindow *win)
{
    sfRectangleShape *bg = sfRectangleShape_create();

    if (!bg)
        return;
    sfRectangleShape_setSize(bg, (sfVector2f){WIDTH, HEIGHT});
    sfRectangleShape_setFillColor(bg, BLUE);
    sfRenderWindow_drawRectangleShape(win, bg, NULL);
    sfRectangleShape_destroy(bg);
}

static menu_t *create_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfVector2f pos_play = {WIDTH / 2 - 250, HEIGHT / 2 + -150};
    sfVector2f pos_options = {WIDTH / 2 - 600, HEIGHT / 2 + -150};
    sfVector2f pos_quit = {WIDTH / 2 + 100, HEIGHT / 2 - 150};

    if (!menu)
        return NULL;
    menu->play = NULL;
    menu->options = NULL;
    menu->quit = NULL;
    menu->background = NULL;
    menu->bg_texture = NULL;
    menu->play = create_button("assets/img/play.png", pos_play);
    menu->options = create_button("assets/img/options.png", pos_options);
    menu->quit = create_button("assets/img/quit.png", pos_quit);
    return menu;
}

void destroy_menu(menu_t *menu)
{
    if (!menu)
        return;
    if (menu->play)
        destroy_button(menu->play);
    if (menu->options)
        destroy_button(menu->options);
    if (menu->quit)
        destroy_button(menu->quit);
    if (menu->background)
        sfSprite_destroy(menu->background);
    if (menu->bg_texture)
        sfTexture_destroy(menu->bg_texture);
    free(menu);
}

static void draw_menu(sfRenderWindow *win, menu_t *menu)
{
    if (!win || !menu)
        return;
    draw_background(win);
    draw_title(win);
    if (menu->play && menu->play->sprite)
        sfRenderWindow_drawSprite(win, menu->play->sprite, NULL);
    if (menu->options && menu->options->sprite)
        sfRenderWindow_drawSprite(win, menu->options->sprite, NULL);
    if (menu->quit && menu->quit->sprite)
        sfRenderWindow_drawSprite(win, menu->quit->sprite, NULL);
}

static sfBool is_button_clicked(button_t *button, sfVector2i mouse_pos,
    sfRenderWindow *win)
{
    sfFloatRect bounds;
    sfVector2f world_pos;

    if (!button || !button->sprite || !win)
        return sfFalse;
    bounds = sfSprite_getGlobalBounds(button->sprite);
    world_pos = sfRenderWindow_mapPixelToCoords(win, mouse_pos, NULL);
    return (world_pos.x >= bounds.left &&
            world_pos.x <= bounds.left + bounds.width &&
            world_pos.y >= bounds.top &&
            world_pos.y <= bounds.top + bounds.height);
}

static void check_window_events(data_t *data, sfEvent event)
{
    if (!data || !data->win)
        return;
    if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(data->win);
}

static void check_button_events(data_t *data, sfEvent event,
    menu_t *menu)
{
    sfVector2i mouse_pos;

    if (!data || !menu || !data->win)
        return;
    if (event.type != sfEvtMouseButtonPressed ||
        event.mouseButton.button != sfMouseLeft)
        return;
    mouse_pos.x = event.mouseButton.x;
    mouse_pos.y = event.mouseButton.y;
    if (menu->play && is_button_clicked(menu->play, mouse_pos, data->win))
        data->scenes = GAME;
    if (menu->options && is_button_clicked(menu->options,
        mouse_pos, data->win)) {
        data->scenes = SETTINGS;
    }
    if (menu->quit && is_button_clicked(menu->quit, mouse_pos, data->win))
        sfRenderWindow_close(data->win);
}

static void handle_menu_events(data_t *data, menu_t *menu)
{
    sfEvent event;

    if (!data || !menu || !data->win)
        return;
    while (sfRenderWindow_pollEvent(data->win, &event)) {
        check_window_events(data, event);
        check_button_events(data, event, menu);
    }
}

size_t display_menu(data_t *data)
{
    if (!data || !data->win)
        return EXIT_ERROR;
    if (data->menu == NULL) {
        data->menu = create_menu();
        if (!data->menu) {
            write_error("Error: Could not create menu\n");
            return EXIT_ERROR;
        }
    }
    handle_menu_events(data, data->menu);
    draw_menu(data->win, data->menu);
    return EXIT_SUCCESS;
}
