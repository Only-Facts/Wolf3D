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
    float angle;

    sfColor color;
    sfRectangleShape *texture;

    sfVector2i ip;

    sfVector2i ippo;
    sfVector2i ipmo;

    sfVector2i jppo;
    sfVector2i jpmo;
} player_t;

typedef struct {
    int **map;
    int size;
} map_t;

typedef struct {
    float angle;
    sfVector2f r;
    float dist;
} ray_t;

typedef struct {
    sfImage *wall;
    sfColor *wall_arr;
} img_t;

typedef struct {
    player_t *p;
    sfRenderWindow *win;
    map_t *map;
    ray_t *r;
    keys_t *keys;
    img_t *img;
    double dtime;
} data_t;

#endif /* wolf3d */
