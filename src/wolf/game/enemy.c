/*
** EPITECH PROJECT, 2025
** wolf3d
** File description:
** ennemy.c
*/

#include "my.h"
#include "math.h"
#include "macro.h"

size_t init_enemy(data_t *data, sfVector2f spawn_pos)
{
    data->e = malloc(sizeof(enemy_t));
    if (!data->e)
        return EXIT_ERROR;
    data->e->position = spawn_pos;
    data->e->dot = sfRectangleShape_create();
    sfRectangleShape_setSize(data->e->dot, (sfVector2f){6, 6});
    sfRectangleShape_setPosition(data->e->dot, data->e->position);
    sfRectangleShape_setFillColor(data->e->dot, RED);
    data->e->speed = 0.01;
    data->e->health = 100;
    data->e->is_alive = 1;
    return EXIT_SUCCESS;
}

static size_t can_move(data_t *data, sfVector2f pos)
{
    int x = (int)((pos.x + 3) / MAP_S);
    int y = (int)((pos.y + 3) / MAP_S);

    if (x < 0 || y < 0 || data->map->map[y][x])
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

static void movement_handler(data_t *data, sfVector2f direction)
{
    sfVector2f new_pos = {
        data->e->position.x + direction.x * data->e->speed * data->dtime,
        data->e->position.y + direction.y * data->e->speed * data->dtime
    };
    sfVector2f temp_x = { new_pos.x, data->e->position.y };
    sfVector2f temp_y = { data->e->position.x, new_pos.y };

    if (can_move(data, temp_x))
        data->e->position.x = new_pos.x;
    if (can_move(data, temp_y))
        data->e->position.y = new_pos.y;
}

void update_enemy(data_t *data)
{
    sfVector2f direction = {0, 0};
    float dist = 0.0;

    if (!data->e->is_alive)
        return;
    direction = (sfVector2f){
        data->p->pos.x - data->e->position.x,
        data->p->pos.y - data->e->position.y
    };
    dist = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (dist < 5)
        return;
    direction.x /= dist;
    direction.y /= dist;
    movement_handler(data, direction);
    sfRectangleShape_setPosition(data->e->dot, data->e->position);
}

size_t is_hit(enemy_t *enemy, sfVector2f player_pos, float player_angle_rad)
{
    float max_distance = 200.0;
    float fov_angle = 10.0 * M_PI / 180.0;
    float distance = 0.0;
    float dot = 0.0;
    sfVector2f to_enemy = {
        enemy->position.x - player_pos.x,
        enemy->position.y - player_pos.y
    };
    sfVector2f aim_dir = {
        cos(player_angle_rad),
        sin(player_angle_rad)
    };

    distance = sqrt(to_enemy.x * to_enemy.x + to_enemy.y * to_enemy.y);
    if (distance > max_distance)
        return EXIT_SUCCESS;
    to_enemy.x /= distance;
    to_enemy.y /= distance;
    dot = (to_enemy.x * aim_dir.x + to_enemy.y * aim_dir.y);
    return dot > cos(fov_angle / 2.0f);
}

void destroy_enemy(enemy_t *enemy)
{
    if (!enemy)
        return;
    if (enemy->dot)
        sfRectangleShape_destroy(enemy->dot);
    free(enemy);
}
