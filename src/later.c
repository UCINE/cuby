/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   later.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 07:34:19 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/05 02:41:37 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"

// int is_walkable_tile(t_gameworld *world, int x, int y)
// {
//     printf("Checking tile: (%d, %d)\n", x, y);

//     if (x < 0 || y < 0 || y >= world->map_info->map_len || x >= world->map_info->max_line)
//     {
//         printf("Tile is out of bounds.\n");
//         return (0);
//     }
//     printf("map len : (%d, %d)\n", world->map_info->map_len , world->map_info->max_line);

//     if (world->map_info->map[y][x] == '1')
//     {
//         printf("Tile is a wall.\n");
//         return (0);
//     }

//     printf("Tile is walkable.\n");
//     return (1);
// }
// int pixel_to_grid(int pixel_coordinate, int tile_size)
// {
//     return (pixel_coordinate / tile_size);
// }

// void move_player(t_gameworld *world, double angle)
// {
//     double old_x = world->map_info->player_x;
//     double old_y = world->map_info->player_y;
//     double new_x = old_x + cos(angle) * 10;
//     double new_y = old_y - sin(angle) * 10;

    // if (is_walkable_tile(world, pixel_to_grid(new_x, ), pixel_to_grid(new_y, world->tile_size)))
    // {
    //     world->map_info->player_x = new_x;
    //     world->map_info->player_y = new_y;
    //     world->map_info->player_y = new_y;
    //     //draw_square(world, new_x, new_y, player_size, 0x0FF000);
    //     world->map_info->player_y = new_y; 
    //     //draw_square(world, new_x, new_y, player_size, 0x0FF000);
    // }
    // if (key == key_forward)
    //     new_y -= step_size;
    // else if (key == key_backward)
    //     new_y += step_size;
    // else if (key == key_left)
    //     new_x -= step_size;
    // else if (key == key_right)
    //     new_x += step_size;

    // if (is_walkable_tile(world, pixel_to_grid(new_x, world->tile_size), pixel_to_grid(new_y, world->tile_size)) &&
    //     is_walkable_tile(world, pixel_to_grid(new_x + player_size, world->tile_size), pixel_to_grid(new_y, world->tile_size)) &&
    //     is_walkable_tile(world, pixel_to_grid(new_x, world->tile_size), pixel_to_grid(new_y + player_size, world->tile_size)) &&
    //     is_walkable_tile(world, pixel_to_grid(new_x + player_size, world->tile_size), pixel_to_grid(new_y + player_size, world->tile_size)))
    // {
    //     draw_square(world, old_x, old_y, player_size, 0x000000);
    //     world->map_info->player_x = new_x;
    //     world->map_info->player_y = new_y;
    //     draw_square(world, new_x, new_y, player_size, 0x0FF000);
    // }
//}

// void    rotate_vector(double angle, t_point2D *vector)
// {
//     double cosAngle;
//     double sinAngle;
//     double prev_x;

//     cosAngle = cos(ROTATION_SPEED * angle);
//     sinAngle = sin(ROTATION_SPEED * angle);
//     prev_x = vector->x;
//     vector->x = prev_x * cosAngle - vector->y * sinAngle;
//     vector->y = prev_x * sinAngle + vector->y * cosAngle;
// }

// void rotate_player(t_gameworld *world, double angle)
// {
//     rotate_vector(angle, &world->player.direction);
//     rotate_vector(angle, &world->player.viewslice);
//     printf("Player Direction: (%f, %f)\n", world->player.direction.x, world->player.direction.y);
// }

// void ft_drawline(t_gameworld *world,int radius,double angle, int color)
// {
//     double x;
//     double y;
//     (void)radius;

//     x =  (double)world->map_info->player_x;
//     y =  (double)world->map_info->player_y;
//     while(1)
//     {
//         x += cos(angle);
//         y -= sin(angle);
//         if (world->map_info->map[(int)y / world->tile_size][(int)x / world->tile_size] == '1')
//         {
//             break;
//         }
//       mlx_pixel_put(world->mlx, world->window,(int)x,(int)y, color);
//     }

// }

// void ft_view(t_gameworld *world,int radius,double angle, int color)
// {
//     int i;

//     i = 0;
//     (void)radius;
//     while (i <= 1000)
//     {
//         ft_drawline(world,world->tile_size,angle - (30 * M_PI / 180) + ((double)i * 60.0 * M_PI / 1000 / 180 ) ,color);
//         i++;
//     }
// }

// int key_hendler(int key, t_gameworld *world)
// {
//     printf("%d\n", key);
//     static double angle = 0;
//     //ft_view(world,world->tile_size, angle,0);
//     if (key == key_forward)
//         move_player(world, angle);
//     else if (key == key_backward)
//         move_player(world, angle - M_PI);
//     else if (key == key_left)
//         move_player(world, angle + M_PI / 2.0);
//     else if (key == key_right)
//         move_player(world, angle - M_PI / 2.0);
//     else if (key == MLX_KEY_Q)
//         angle+= 0.05;
//         //rotate_player(world, -1);
//     else if (key == MLX_KEY_E)
//         angle-= 0.05;
//     //rotate_player(world, 1);
//     else if (key == KEY_ESC)
//         exit(0);
//     //ft_view(world,world->tile_size, angle,0x00ffff);
//     return (0);
// }


