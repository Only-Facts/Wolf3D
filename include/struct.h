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
    #define MAP_Y 16
    #define MAP_X 16
    #define MAP_S 10

typedef struct {
    int z;
    int s;
    int q;
    int d;
    int left;
    int right;
} keys_t;

typedef struct {
    sfVector2f pos;
    sfVector2f delta;
    float angle;
    sfSprite *sprite;
    sfColor color;
    sfRectangleShape *texture;
    sfVector2i ip;
    sfVector2i ippo;
    sfVector2i ipmo;
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
    keys_t *keys;
} data_t;

#endif /* wolf3d */
