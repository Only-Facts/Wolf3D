/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** audio.c
*/

#include "my.h"
#include "struct.h"
#include "macro.h"
#include <SFML/Audio.h>

static sfMusic *load_music(const char *filepath)
{
    sfMusic *music = NULL;

    if (!filepath)
        return NULL;
    music = sfMusic_createFromFile(filepath);
    if (!music)
        return NULL;
    sfMusic_setLoop(music, sfTrue);
    sfMusic_setVolume(music, 50);
    return music;
}

size_t init_audio(data_t *data)
{
    data->audio = malloc(sizeof(audio_t));
    if (!data->audio)
        return EXIT_ERROR;
    data->audio->menu_music = load_music("assets/audio/menu_theme.ogg");
    data->audio->game_music = load_music("assets/audio/game_theme.ogg");
    if (!data->audio->menu_music || !data->audio->game_music)
        return EXIT_ERROR;
    data->audio->current_playing = NONE_MUSIC;
    return EXIT_SUCCESS;
}

void update_music(data_t *data)
{
    if (!data || !data->audio)
        return;
    if (data->scenes == MENU || data->scenes == SETTINGS)
        play_menu_music(data);
    else if (data->scenes == GAME)
        play_game_music(data);
}

void play_menu_music(data_t *data)
{
    if (!data || !data->audio || data->audio->current_playing == MENU_MUSIC)
        return;
    if (data->audio->current_playing == GAME_MUSIC)
        sfMusic_stop(data->audio->game_music);
    sfMusic_play(data->audio->menu_music);
    data->audio->current_playing = MENU_MUSIC;
}

void play_game_music(data_t *data)
{
    if (!data || !data->audio || data->audio->current_playing == GAME_MUSIC)
        return;
    if (data->audio->current_playing == MENU_MUSIC)
        sfMusic_stop(data->audio->menu_music);
    sfMusic_play(data->audio->game_music);
    data->audio->current_playing = GAME_MUSIC;
}

void destroy_audio(audio_t *audio)
{
    if (!audio)
        return;
    if (audio->menu_music) {
        sfMusic_stop(audio->menu_music);
        sfMusic_destroy(audio->menu_music);
    }
    if (audio->game_music) {
        sfMusic_stop(audio->game_music);
        sfMusic_destroy(audio->game_music);
    }
    free(audio);
}