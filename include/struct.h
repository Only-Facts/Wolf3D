/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** struct.h
*/

#ifndef STRUCT
    #define STRUCT
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

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

enum music_type {
    NONE_MUSIC,
    MENU_MUSIC,
    GAME_MUSIC,
};

typedef struct {
    sfMusic *menu_music;
    sfMusic *game_music;
    enum music_type current_playing;
} audio_t;

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
    sfText *play;
    sfText *options;
    sfText *quit;
    sfText *fps_text;
    sfText *volume_text;
    sfSprite *background;
    sfTexture *bg_texture;
    int fps_limit;
    int volume_level;
} menu_t;

typedef struct {
    enum scenes scenes;
    player_t *p;
    sfRenderWindow *win;
    map_t *map;
    ray_t *r;
    keys_t *keys;
    img_t *img;
    menu_t *menu;
    audio_t *audio;
    double dtime;
    size_t FOV;
} data_t;

#endif /* wolf3d */
