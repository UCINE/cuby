/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:34:19 by lahamoun          #+#    #+#             */
/*   Updated: 2023/10/26 16:29:11 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_walkable_tile(t_gameworld *world, int x, int y)
{
    printf("ok");
    if (x < 0 || y < 0 || y >= world->map_info->map_len || x >= world->map_info->max_line)
        return (0);
    if (world->map_info->map[y][x] == '1')
        return (0); 
    return (1);
}

void move_player(t_gameworld *world, t_keys key)
{
    int new_x = world->map_info->player_x;
    int new_y = world->map_info->player_y;

    if (key == key_forward)
        new_x -= 1;
    else if (key == key_backward)
        new_x += 1;
    else if (key == key_left)
        new_y -= 1;
    else if (key == key_right)
        new_y += 1;

    if (!is_walkable_tile(world, new_x, new_y))
        return;
    draw_square(world, world->map_info->player_y , world->map_info->player_x, player_size, 0x000000);
    world->map_info->player_x = new_x;
    world->map_info->player_y = new_y;
    draw_square(world, world->map_info->player_y, world->map_info->player_x , player_size, 0x0FF000);
}

void    rotate_vector(double angle, t_point2D *vector)
{
    double cosAngle;
    double sinAngle;
    double prev_x;

    cosAngle = cos(ROTATION_SPEED * angle);
    sinAngle = sin(ROTATION_SPEED * angle);
    prev_x = vector->x;
    vector->x = prev_x * cosAngle - vector->y * sinAngle;
    vector->y = prev_x * sinAngle + vector->y * cosAngle;
}

void    rotate_player(t_gameworld *world, double angle)
{
    rotate_vector(angle, &world->player.direction);
    rotate_vector(angle, &world->player.viewslice);
}

int key_hendler(int key, t_gameworld *world)
{
    if (key == key_forward)
        move_player(world, key_forward);
    else if (key == key_backward)
        move_player(world, key_backward);
    else if (key == key_left)
        move_player(world, key_left);
    else if (key == key_right)
        move_player(world, key_right);
    // else if (key == key_left)
    //     rotate_player(world, -1);
    // else if (key == key_right)
    //     rotate_player(world, 1);
    else if (key == KEY_ESC)
        exit(0);
    return (0);
}

