/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** struct.h
*/

#ifndef STRUCT
    #define STRUCT
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/Rect.h>
    #include <SFML/System/Vector2.h>
    #include <stdbool.h>

/* MAP */
    #define MAP_Y 16
    #define MAP_X 16
    #define MAP_S 16

enum scenes {
    MENU,
    GAME,
    SETTINGS,
    PAUSE,
    END,
};

typedef struct enemy_s {
    sfVector2f position;
    float speed;
    int health;
    size_t is_alive;
    sfRectangleShape *dot;
} enemy_t;

typedef struct part_t {
    float x;
    float y;
    float z;

    float vx;
    float vy;
    float vz;

    float time;
    float angle;
    float spread;
    float speed;

} part_t;

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
    sfVector2i img_size;
    sfIntRect idle_rect;
    sfIntRect shoot_rect;
    sfIntRect recoil_rect;
    sfClock *clock;
} weapon_t;

typedef struct {
    int z;
    int s;
    int q;
    int d;
    int left;
    int right;
    int space;
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
    float scale;
    sfBool is_animating;
    sfBool is_shrinking;
    float target_scale;
    float animation_speed;
    sfClock *clock;
} button_anim_t;

typedef struct {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f position;
    button_anim_t *anim;
} button_t;

typedef struct {
    button_t *play;
    button_t *options;
    button_t *quit;
    sfText *fps_text;
    sfSprite *background;
    sfTexture *bg_texture;
    int fps_limit;
} menu_t;

typedef struct {
    enum scenes scenes;
    player_t *p;
    enemy_t *e;
    sfRenderWindow *win;
    map_t *map;
    ray_t *r;
    keys_t *keys;
    img_t *img;
    menu_t *menu;
    double dtime;
    size_t FOV;
    size_t fullscreen;
    weapon_t **w;
    part_t *part;
    size_t wnb;
    int flash;
    size_t part_count;
} data_t;

#endif /* wolf3d */
