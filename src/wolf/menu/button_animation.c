/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** button_animation.c
*/

#include "my.h"
#include "macro.h"

button_anim_t *create_button_anim(void)
{
    button_anim_t *anim = malloc(sizeof(button_anim_t));

    if (!anim)
        return NULL;
    anim->scale = 1.0f;
    anim->is_animating = sfFalse;
    anim->is_shrinking = sfFalse;
    anim->target_scale = 0.85f;
    anim->animation_speed = 0.05f;
    anim->clock = sfClock_create();
    if (!anim->clock) {
        free(anim);
        return NULL;
    }
    return anim;
}

void destroy_button_anim(button_anim_t *anim)
{
    if (!anim)
        return;
    if (anim->clock)
        sfClock_destroy(anim->clock);
    free(anim);
}

void start_button_animation(button_t *button)
{
    if (!button || !button->anim)
        return;
    button->anim->is_animating = sfTrue;
    button->anim->is_shrinking = sfTrue;
    sfClock_restart(button->anim->clock);
}

void update_button_animation(button_t *button, float dtime)
{
    button_anim_t *anim;

    if (!button || !button->anim || !button->anim->is_animating)
        return;
    anim = button->anim;
    if (anim->is_shrinking) {
        anim->scale -= anim->animation_speed * dtime;
        if (anim->scale <= anim->target_scale) {
            anim->scale = anim->target_scale;
            anim->is_shrinking = sfFalse;
        }
    } else {
        anim->scale += anim->animation_speed * dtime;
        if (anim->scale >= 1.0f) {
            anim->scale = 1.0f;
            anim->is_animating = sfFalse;
        }
    }
    sfSprite_setScale(button->sprite,
        (sfVector2f){anim->scale, anim->scale});
}

void check_button_clicks(data_t *data, sfVector2i mouse_pos,
    menu_t *menu)
{
    sfBool action_play = sfFalse;
    sfBool action_options = sfFalse;
    sfBool action_quit = sfFalse;

    if (!data || !menu || !data->win)
        return;
    handle_button_click(menu->play, mouse_pos, data->win, &action_play);
    handle_button_click(menu->options, mouse_pos, data->win, &action_options);
    handle_button_click(menu->quit, mouse_pos, data->win, &action_quit);
    if (action_play)
        data->scenes = GAME;
    if (action_options)
        data->scenes = SETTINGS;
    if (action_quit)
        sfRenderWindow_close(data->win);
}
