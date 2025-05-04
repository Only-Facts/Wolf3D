/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** fps.c
*/

#include <SFML/Graphics.h>
#include <stdio.h>
#include "macro.h"

void draw_fps(sfRenderWindow *win, double fps)
{
    char text[20] = {0};
    sfText *display = sfText_create();

    snprintf(text, 20, "FPS: %.2f", fps);
    sfText_setFont(display, FONT);
    sfText_setCharacterSize(display, 12);
    sfText_setString(display, text);
    sfText_setPosition(display, (sfVector2f){WIDTH - 90, 0});
    sfText_setFillColor(display, WHITE);
    sfRenderWindow_drawText(win, display, NULL);
    sfText_destroy(display);
}
