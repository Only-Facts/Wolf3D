/*
** EPITECH PROJECT, 2025
** template
** File description:
** init.c
*/

#include "my.h"
#include "struct.h"

static void free_data(data_t *data)
{
    if (data->menu)
        destroy_menu(data->menu);
    if (data->audio)
        destroy_audio(data->audio);
    sfRectangleShape_destroy(data->p->texture);
    free(data->p);
    free(data->r);
    for (size_t y = 0; y < MAP_Y; y++)
        free(data->map->map[y]);
    free(data->map->map);
    free(data->map);
    free(data->keys);
    free(data->img->wall_arr);
    sfImage_destroy(data->img->wall);
    free(data->img);
    sfRenderWindow_destroy(data->win);
    free(data);
}

static size_t init_img(data_t *data)
{
    size_t index = 0;

    data->img = malloc(sizeof(img_t));
    if (!data->img)
        return EXIT_ERROR;
    data->img->wall = sfImage_createFromFile("assets/img/wall.png");
    if (!data->img->wall)
        return EXIT_ERROR;
    data->img->wall_arr = malloc(sizeof(sfColor) * (32 * 32 + 1));
    if (!data->img->wall_arr)
        return EXIT_ERROR;
    for (size_t y = 0; y < 32; y++)
        for (size_t x = 0; x < 32; x++) {
            data->img->wall_arr[index] =
                sfImage_getPixel(data->img->wall, x, y);
            index++;
        }
    data->img->wall_arr[index] = (sfColor){-1, -1, -1, -1};
    return EXIT_SUCCESS;
}

static data_t *init_struct(void)
{
    data_t *data = malloc(sizeof(data_t));

    data->dtime = 0;
    data->scenes = MENU;
    data->menu = NULL;
    data->audio = NULL;
    data->FOV = 80;
    data->flash = -1;
    data->wnb = 0;
    data->ftext = NULL;
    if (init_window(data) || init_map(data) || init_player(data) ||
        init_ray(data) || init_keys(data) || init_img(data) ||
        init_enemy(data, (sfVector2f){4.5 * MAP_S, 4.5 * MAP_S}) ||
        init_audio(data))
        return NULL;
    return data;
}

static size_t init_wolf(void)
{
    data_t *data = init_struct();
    int exit = EXIT_SUCCESS;

    if (!data)
        return EXIT_ERROR;
    exit = loop(data);
    free_data(data);
    return exit;
}

static size_t print_help(void)
{
    char *mess = read_file("assets/txt/help");

    write_mess(mess);
    free(mess);
    return EXIT_HELP;
}

static size_t handle_error(int argc, const char *argv[])
{
    if (argv && argv[1] && (str_cmp(argv[1], "-h") == 0 ||
        str_cmp(argv[1], "--help") == 0) && get_len(argv[1]) > 0)
        return print_help();
    if (!getenv("DISPLAY"))
        return write_error("Error 84: Bad DISPLAY environement variable.\n");
    if (argc > 1)
        return write_error("Error 84: Bad usage!\n\n"
        "Usage: ./wolf3d [OPTIONS]\n"
        "Options:\n\t-h\n\t--help\n");
    return EXIT_SUCCESS;
}

int initialise(int argc, const char *argv[])
{
    switch (handle_error(argc, argv)) {
        case EXIT_HELP:
            return EXIT_SUCCESS;
        case EXIT_ERROR:
            return EXIT_ERROR;
        default:
            return init_wolf();
    }
}
