/*
** EPITECH PROJECT, 2024
** header
** File description:
** my.h
*/

#ifndef MY
    #define MY

/* Mandatory */
    #include "struct.h"
    #include <stdlib.h>
    #include <unistd.h>

/* CSFML */
    #include <SFML/System.h>
    #include <SFML/Window.h>

enum {
    EXIT_ERROR = 84,
    EXIT_FAIL = -1,
    EXIT_HELP = 2029,
    COUT = 1,
    CERR = 2,
};

/* >------ Project ------< */

/* init.c */
int initialise(int argc, const char *argv[]);

/* loop.c */
size_t loop(data_t *data);

/* scenes */
size_t scenes(data_t *data, const double fps);

/* window.c */
size_t init_window(data_t *data);
void change_screen_mode(data_t *data);

/* audio.c */
size_t init_audio(data_t *data);
void update_music(data_t *data);
void play_menu_music(data_t *data);
void play_game_music(data_t *data);
void destroy_audio(audio_t *audio);
void update_music_volume(data_t *data);

/* >------ Game ------< */

/* ceiling.c */
void draw_ceiling(data_t *data);

/* draw.c */
void draw_rays(data_t *data);
void draw(data_t *data);

/* ennemy.c */
size_t init_enemy(data_t *data, sfVector2f spawn_pos);
void update_enemy(data_t *data);
size_t is_hit(enemy_t *enemy, sfVector2f player_pos, float player_angle_rad);
void destroy_enemy(enemy_t *enemy);

/* event.c */
size_t init_keys(data_t *data);
void event(data_t *data);

/* call_to_event */
void call_to_event(data_t *data, sfEvent event);

/* floor.c */
void draw_floor(data_t *data);

/* fps.c */
void draw_fps(sfRenderWindow *win, double fps);

/* fire_shot.c */
void init_f_burst(data_t *data);
void fire_shot(data_t *data);

/* map.c */
size_t init_map(data_t *data);

/* player.c */
void draw_player(data_t *data);
size_t init_player(data_t *data);

size_t weapon(data_t *data);

/* raycaster.c */
size_t init_ray(data_t *data);
sfVector3f check_h_lines(data_t *data);
sfVector3f check_v_lines(data_t *data);

/* >------ Menu ------< */

/* button_animation.c */
button_anim_t *create_button_anim(void);
void destroy_button_anim(button_anim_t *anim);
void start_button_animation(button_t *button);
void update_button_animation(button_t *button, float dtime);
void check_button_clicks(data_t *data, sfVector2i mouse_pos, menu_t *menu);
void handle_button_click(button_t *button, sfVector2i mouse_pos,
    sfRenderWindow *win, sfBool *action);
/* create_button.c */
void draw_background(sfRenderWindow *win);
void draw_title(sfRenderWindow *win);
void destroy_menu(menu_t *menu);

/* menu.c */
size_t display_menu(data_t *data);

/* handle_button_hover.c */
void handle_button_hover(data_t *data);

/* >------ Settings ------< */

/* settings.c */
size_t display_settings(data_t *data);
void handle_fps_text_click(data_t *data, sfVector2i mouse_pos);
void handle_volume_text_click(data_t *data, sfVector2i mouse_pos);

/* settings_events.c */
void handle_settings_events(data_t *data);

/* fps_settings.c */
sfText *create_fps_text(int fps_limit);
sfText *create_volume_text(int volume_level);
void update_fps_text(menu_t *menu);
void update_volume_text(menu_t *menu);
void toggle_fps_limit(data_t *data);

/* toggle_screen.c */
sfText *create_mode_text(data_t *data);
void update_mode_text(data_t *data);

/* >------ Lib ------< */

/* lenght */
size_t get_len(const char *str);
size_t get_array_len(const char **array);
size_t get_nb_len(const int nb);

/* dup */
char *str_dup(const char *str);
char *strn_dup(const char *str, const size_t n);

/* cpy */
void str_cpy(char *a, const char *b);
void strn_cpy(char *a, const char *b, const size_t n);
void array_cpy(char **arr, const char **to_cpy);
void arrayn_cpy(char **arr, const char **to_cpy, const size_t n);

/* cat */
void str_cat(char *dest, const char *src);
char *str_catalloc(const char *str, const char *add);
void array_cat(char **dest, const char **src);
char **array_catalloc(const char **arr, const char **add);

/* write */
int write_mess(const char *mess);
int write_error(const char *mess);
int write_arr(const char **arr);

/* cmp */
int str_cmp(const char *a, const char *b);
int strn_cmp(char const *s1, char const *s2, const size_t n);

/* slice */
char **slice(const char *str, const char *separators);
char **cut(const char *str, const char *sep);

/* convert */
int str_to_int(const char *str);
char *int_str(int nb);

/* file */
char *read_file(const char *path);

/* pointers */
void swap_int(int *a, int *b);
void swap_str(char **a, char **b);

/* free */
void free_arr(char **arr);

#endif
