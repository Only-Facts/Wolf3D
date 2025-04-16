/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** struct.h
*/

#ifndef STRUCT
    #define STRUCT
    #include <SFML/Graphics.h>

typedef struct {
    sfVector2f pos;
    sfSprite *sprite;
    sfColor color;
    sfRectangleShape *texture;
} player_t;

typedef struct {
    player_t *player;
    sfRenderWindow *window;
} data_t;

#endif /* wolf3d */
