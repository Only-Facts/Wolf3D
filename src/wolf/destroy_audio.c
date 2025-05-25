/*
** EPITECH PROJECT, 2024
** Wolf3D
** File description:
** destroy_audio.c
*/

#include "macro.h"
#include "struct.h"
#include "my.h"

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