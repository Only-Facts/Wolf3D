/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** macro.h
*/

#ifndef MACRO_H
    #define MACRO_H
    #include <SFML/Graphics.h>

    /* TITLE */
    #define TITLE "Your local low cost Wolfenstein 3D from 1992 ultimate"

    /* SCREEN */
    #define WIDTH 1300
    #define HEIGHT 512

    /* FONT */
    #define FONT sfFont_createFromFile("assets/fonts/fira.ttf")

    /* Colors */
    #define BLACK sfColor_fromRGB(10, 10, 10)
    #define GREY sfColor_fromRGB(50, 50, 50)
    #define RED sfColor_fromRGB(100, 20, 30)
    #define GREEN sfColor_fromRGB(20, 100, 20)
    #define BLUE sfColor_fromRGB(20, 20, 100)
    #define WHITE sfColor_fromRGB(220, 220, 220)

    /* PI */
    #define PI 3.1415926535
    #define P2 PI / 2
    #define P3 3 * PI / 2

    /* RADIANS */
    #define RAD 0.0174533
    #define DEG_TO_RAD(a) (a * PI / 180.0)

#endif /* MACRO_H */
