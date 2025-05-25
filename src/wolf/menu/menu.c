/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** menu.c
*/

#include "my.h"
#include "macro.h"

static void configure_menu_button(sfText *button, sfFont *font,
    const char *label, sfVector2f position)
{
    sfText_setFont(button, font);
    sfText_setCharacterSize(button, 60);
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
    sfVector2f pos_options = {WIDTH / 2.0f, HEIGHT / 2.0f + 200};
    sfVector2f pos_quit = {WIDTH / 2.0f, HEIGHT / 2.0f + 300};

    menu->play = sfText_create();
    menu->options = sfText_create();
    menu->quit = sfText_create();
    configure_menu_button(menu->play, font, "PLAY", pos_play);
    configure_menu_button(menu->options, font, "OPTIONS", pos_options);
    configure_menu_button(menu->quit, font, "QUIT", pos_quit);
}

static menu_t *create_menu(void)
{
    menu_t *menu = malloc(sizeof(menu_t));
    sfFont *font = FONT;

    if (!menu || !font)
        return NULL;
    init_menu_buttons(menu, font);
    menu->fps_text = NULL;
    menu->volume_text = NULL;
    menu->background = NULL;
    menu->bg_texture = NULL;
    menu->fps_limit = 60;
    menu->volume_level = 50;
    return menu;
}

static void draw_menu(sfRenderWindow *win, menu_t *menu)
{
    if (!win || !menu)
        return;
    draw_background(win);
    draw_title(win);
    if (menu->play)
        sfRenderWindow_drawText(win, menu->play, NULL);
    if (menu->options)
        sfRenderWindow_drawText(win, menu->options, NULL);
    if (menu->quit)
        sfRenderWindow_drawText(win, menu->quit, NULL);
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

static void check_menu_clicks(data_t *data, sfVector2i mouse_pos,
    menu_t *menu)
{
    if (!data || !menu || !data->win)
        return;
    if (is_text_clicked(menu->play, mouse_pos, data->win))
        data->scenes = GAME;
    if (is_text_clicked(menu->options, mouse_pos, data->win))
        data->scenes = SETTINGS;
    if (is_text_clicked(menu->quit, mouse_pos, data->win))
        sfRenderWindow_close(data->win);
}

static void check_window_events(data_t *data, sfEvent event)
{
    if (!data || !data->win)
        return;
    if (event.type == sfEvtClosed)
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
    check_menu_clicks(data, mouse_pos, menu);
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
    handle_button_hover(data);
    draw_menu(data->win, data->menu);
    return EXIT_SUCCESS;
}
