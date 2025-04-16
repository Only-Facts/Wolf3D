/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** struct.h
*/

#ifndef STRUCT
    #define STRUCT
    #include <SFML/Graphics.h>

    /* MAP */
    #define MAP_Y 8
    #define MAP_X 8
    #define MAP_S 64

typedef struct {
    sfVector2f pos;
    sfVector2f delta;
    float angle;
    sfSprite *sprite;
    sfColor color;
    sfRectangleShape *texture;
} player_t;

typedef struct {
    int **map;
    int size;
} map_t;

typedef struct {
    float angle;
} ray_t;

typedef struct {
    player_t *p;
    sfRenderWindow *win;
    map_t *map;
    ray_t *r;
} data_t;

#endif /* wolf3d */
