/*
** EPITECH PROJECT, 2025
** template
** File description:
** init.c
*/

#include "my.h"

static void free_data(data_t *data)
{
    sfRenderWindow_destroy(data->window);
    free(data);
}

static data_t *init_struct(void)
{
    data_t *data = malloc(sizeof(data_t));

    if (init_window(data) == EXIT_ERROR)
        return NULL;
    return data;
}

static size_t init_wolf(void)
{
    data_t *data = init_struct();

    if (loop(data) == EXIT_ERROR)
        return EXIT_ERROR;
    free_data(data);
    return EXIT_SUCCESS;
}

static size_t print_help(void)
{
    write_mess(read_file("assets/txt/help"));
    return EXIT_HELP;
}

static size_t check_env(const char *env[])
{
    for (size_t i = 0; env[i]; i++)
        if (str_cmp(env[i], DISPLAY) == 0 &&
        get_len(env[i]) == get_len(DISPLAY))
            return EXIT_SUCCESS;
    return EXIT_ERROR;
}

static size_t handle_error(int argc, const char *argv[], const char *env[])
{
    if (argv && argv[1] && (str_cmp(argv[1], "-h") == 0 ||
        str_cmp(argv[1], "--help") == 0) && get_len(argv[1]) > 0)
        return print_help();
    if (check_env(env) == EXIT_ERROR)
        return write_error("Error 84: Bad DISPLAY environement variable.\n");
    if (argc > 1)
        return write_error("Error 84: Bad usage!\n\n"
        "Usage: ./wolf3d [OPTIONS]\n"
        "Options:\n\t-h\n\t--help\n");
    return EXIT_SUCCESS;
}

int initialise(int argc, const char *argv[], const char *env[])
{
    switch (handle_error(argc, argv, env)) {
        case EXIT_HELP:
            return EXIT_SUCCESS;
        case EXIT_ERROR:
            return EXIT_ERROR;
        default:
            return init_wolf();
    }
}
