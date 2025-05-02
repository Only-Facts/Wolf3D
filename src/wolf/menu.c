/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** menu.c
*/

#include "my.h"
#include "macro.h"
#include "struct.h"

static sfTexture *load_button_texture(const char *path)
{
    return sfTexture_createFromFile(path, NULL);
}

static sfSprite *init_button_sprite(sfTexture *texture, sfVector2f pos)
{
    sfSprite *sprite = sfSprite_create();

    if (!sprite)
        return NULL;
    sfSprite_setTexture(sprite, texture, sfTrue);
    sfSprite_setPosition(sprite, pos);
    return sprite;
}

static button_t *create_button(const char *path, sfVector2f pos)
{
    button_t *button = malloc(sizeof(button_t));

    if (!button)
        return NULL;
    button->position = pos;
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

static void destroy_button(button_t *button)
{
    if (!button)
        return;
    if (button->sprite)
        sfSprite_destroy(button->sprite);
    if (button->texture)
        sfTexture_destroy(button->texture);
    free(button);
}

static sfBool is_button_clicked(button_t *button, sfVector2i mouse_pos,
    sfRenderWindow *win)
{
    sfFloatRect bounds = sfSprite_getGlobalBounds(button->sprite);
    sfVector2f world_pos = sfRenderWindow_mapPixelToCoords(win,
        mouse_pos, NULL);

    return (world_pos.x >= bounds.left && 
            world_pos.x <= bounds.left + bounds.width &&
            world_pos.y >= bounds.top && 
            world_pos.y <= bounds.top + bounds.height);
}

static void check_window_events(data_t *data, sfEvent event)
{
    if (event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape))
        sfRenderWindow_close(data->win);
}

static void check_button_events(data_t *data, sfEvent event,
    button_t *button, sfBool *in_menu)
{
    sfVector2i mouse_pos;

    if (event.type != sfEvtMouseButtonPressed || 
        event.mouseButton.button != sfMouseLeft)
        return;
    mouse_pos.x = event.mouseButton.x;
    mouse_pos.y = event.mouseButton.y;
    if (is_button_clicked(button, mouse_pos, data->win))
        *in_menu = sfFalse;
}

static void handle_menu_events(data_t *data, button_t *button,
    sfBool *in_menu)
{
    sfEvent event;

    while (sfRenderWindow_pollEvent(data->win, &event)) {
        check_window_events(data, event);
        check_button_events(data, event, button, in_menu);
    }
}

static void run_menu_loop(data_t *data, button_t *button)
{
    sfBool in_menu = sfTrue;

    while (sfRenderWindow_isOpen(data->win) && in_menu) {
        sfRenderWindow_clear(data->win, GREY);
        handle_menu_events(data, button, &in_menu);
        sfRenderWindow_drawSprite(data->win, button->sprite, NULL);
        sfRenderWindow_display(data->win);
    }
}

size_t display_menu(data_t *data)
{
    button_t *play_button = create_button("assets/img/play.png",
                                         (sfVector2f){400, 0});
    
    if (!play_button) {
        write_error("Error: Could not create play button\n");
        return EXIT_ERROR;
    }
    run_menu_loop(data, play_button);
    destroy_button(play_button);
    return EXIT_SUCCESS;
}