/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** weapon
*/

#include "macro.h"
#include "my.h"
#include "struct.h"
#include <stdlib.h>

static void init_rect(data_t *data)
{
    sfImage *image = sfImage_createFromFile("assets/img/weap_rec.png");
    sfVector2u img_size = sfImage_getSize(image);

    if (!data)
    return;
    data->w[data->wnb]->idle_rect =
    (sfIntRect){0, 0, img_size.x, img_size.y / 3};
    data->w[data->wnb]->shoot_rect =
    (sfIntRect){0, img_size.y / 3, img_size.x, (img_size.y / 3)};
    data->w[data->wnb]->recoil_rect =
    (sfIntRect){0, (img_size.y / 3) * 2, img_size.x, img_size.y};
    sfImage_destroy(image);
}

static void load_weapon(data_t *data)
{
    data->wnb = 0;
    data->w[data->wnb]->sprite = malloc(sizeof(sprite_t));
    data->w[data->wnb]->sprite->s = sfSprite_create();
    if (!data->w[data->wnb]->sprite->s)
        return;
    data->w[data->wnb]->sprite->t =
    sfTexture_createFromFile("assets/img/weap_rec.png", NULL);
    data->w[data->wnb]->sprite->size = (sfVector2f){132, 416};
    data->w[data->wnb]->sprite->pos =
    (sfVector2f){WIDTH / 2 - 115, HEIGHT / 2 + 30};
    sfSprite_setTexture(data->w[data->wnb]->sprite->s,
    data->w[data->wnb]->sprite->t, sfTrue);
    init_rect(data);
    sfSprite_setTextureRect(data->w[data->wnb]->sprite->s,
    data->w[data->wnb]->idle_rect);
    sfSprite_setPosition(data->w[data->wnb]->sprite->s,
    data->w[data->wnb]->sprite->pos);
    sfSprite_setScale(data->w[data->wnb]->sprite->s, (sfVector2f){1.2, 1.2});
}

static void init_weapon(data_t *data)
{
    if (!data)
        return;
    data->w = malloc(sizeof(weapon_t *) * 2);
    data->w[0] = malloc(sizeof(weapon_t));
    data->w[1] = malloc(sizeof(weapon_t));
}

static void handle_shoot(data_t *data)
{
    if (!data)
        return;
    data->wnb = 0;
    if (sfKeyboard_isKeyPressed(sfKeySpace))
        sfSprite_setTextureRect(data->w[data->wnb]->sprite->s,
        data->w[data->wnb]->shoot_rect);
}

size_t weapon(data_t *data)
{
    if (!data)
        return EXIT_ERROR;
    init_weapon(data);
    init_rect(data);
    load_weapon(data);
    handle_shoot(data);
    sfRenderWindow_drawSprite(data->win, data->w[0]->sprite->s, NULL);
    return EXIT_SUCCESS;
}
