/*
** EPITECH PROJECT, 2025
** Wolf3D
** File description:
** weapon
*/

#include "macro.h"
#include "my.h"
#include "struct.h"
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/System/Vector2.h>
#include <stdlib.h>


static void load_weapon(data_t *data)
{
    data->wnb = 0;
    data->w[data->wnb]->sprite = malloc(sizeof(sprite_t));
    data->w[data->wnb]->sprite->s = sfSprite_create();
    if (!data->w[data->wnb]->sprite->s)
        return;
    data->w[data->wnb]->sprite->t =
    sfTexture_createFromFile("assets/img/weapon.png", NULL);
    data->w[data->wnb]->sprite->size = (sfVector2f){102 * 2, 82 * 2};
    data->w[data->wnb]->sprite->pos = (sfVector2f){WIDTH / 2 -
    data->w[data->wnb]->sprite->size.x / 2,
    HEIGHT / 2 + 30};
    sfSprite_setTexture(data->w[data->wnb]->sprite->s,
    data->w[data->wnb]->sprite->t, sfFalse);
    sfSprite_setPosition(data->w[data->wnb]->sprite->s, data->w[data->wnb]->sprite->pos);
    sfSprite_setScale(data->w[data->wnb]->sprite->s, (sfVector2f){2, 2});
}

static void init_weapon(data_t *data)
{
    if (!data)
        return;
    data->w = malloc(sizeof(weapon_t *) * 2);
    data->w[0] = malloc(sizeof(weapon_t));
    data->w[1] = malloc(sizeof(weapon_t));
}

size_t weapon(data_t *data)
{
    if (!data)
        return EXIT_ERROR;
    init_weapon(data);
    load_weapon(data);
    sfRenderWindow_drawSprite(data->win, data->w[0]->sprite->s, NULL);
    return EXIT_SUCCESS;
}
