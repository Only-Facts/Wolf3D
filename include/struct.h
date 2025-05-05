/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** struct.h
*/

#ifndef STRUCT
    #define STRUCT
    #include <SFML/Graphics.h>
    #include <stdbool.h>

    /* MAP */
    #define MAP_Y 16
    #define MAP_X 16
    #define MAP_S 10

enum scenes {
    MENU,
    GAME,
    SETTINGS,
    PAUSE,
    END,
};

typedef struct {
    sfSprite *s;
    sfTexture *t;
    sfVector2f pos;
    sfVector2f size;
} sprite_t;

typedef struct {
    char name[50];
    bool is_firearm;
    size_t ammo;
    sprite_t *sprite;
} weapon_t;

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
    enum scenes scenes;
    player_t *p;
    sfRenderWindow *win;
    map_t *map;
    ray_t *r;
    keys_t *keys;
    img_t *img;
    double dtime;
    weapon_t **w;
    int flash;
} data_t;

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
} button_t;

#endif /* wolf3d */
