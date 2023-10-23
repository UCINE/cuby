/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:34:19 by lahamoun          #+#    #+#             */
/*   Updated: 2023/10/23 19:00:12 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    move_player(t_gameworld *world, t_keys key)
{
    double dy;
    double dx;
    
    printf("Yo");
    dy = world->player.direction.y;
    dx = world->player.direction.x;
    if (key == key_forward)
    {
        world->map_info->player_x += dx * PLAYER_SPEED;
        world->map_info->player_y += dy * PLAYER_SPEED;
    }
    else if (key == key_backward)
    {
        world->map_info->player_x -= dx * PLAYER_SPEED;
        world->map_info->player_y -= dy * PLAYER_SPEED;
    }
    else if (key == key_left)
    {
        world->map_info->player_x -= dy * PLAYER_SPEED;
        world->map_info->player_y += dx * PLAYER_SPEED;
    }
    else if (key == key_right)
    {
        world->map_info->player_x += dy * PLAYER_SPEED;
        world->map_info->player_y -= dx * PLAYER_SPEED;
    }
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
    printf("%d\n", key);
    if (key == MLX_KEY_W)
        move_player(world, key_forward);
    else if (key == MLX_KEY_S)
        move_player(world, key_backward);
    else if (key == MLX_KEY_A)
        rotate_player(world, -1);
    else if (key == MLX_KEY_D)
        rotate_player(world, 1);
    else if (key == KEY_ESC)
        exit(0);
    // else
    // printf("Unexpected key: %d\n", key);
    return (0);
}
