/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/05 03:07:37 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawCircle(t_gameworld *data, int x, int y)
{
	my_mlx_pixel_put(data, data->map_info->player_x+x, data->map_info->player_y+y, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x-x, data->map_info->player_y+y, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x+x, data->map_info->player_y-y, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x-x, data->map_info->player_y-y, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x+y, data->map_info->player_y+x, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x-y, data->map_info->player_y+x, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x+y, data->map_info->player_y-x, 0xFFFFFF);
	my_mlx_pixel_put(data, data->map_info->player_x-y, data->map_info->player_y-x, 0xFFFFFF);
}

void circleBres(t_gameworld *data, int r)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	drawCircle(data, x, y);
	while (y >= x)
	{
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		drawCircle(data, x, y);
	}
}
void    realloc_image(t_gameworld *world)
{
    world->imageToDraw.img = mlx_new_image(world->connection, 
    world->w * 40, world->h * 40);
    world->imageToDraw.addr = mlx_get_data_addr(world->imageToDraw.img,
		&world->imageToDraw.bits_per_pixel, &world->imageToDraw.line_length,
		&world->imageToDraw.endian);
}

// void ray_create(t_gameworld *data, double ray_y, double ray_x)
// {
//     double i = -0.5;
//     //int j = 1000;
//     while (i <= 0.5)
//     {
//         data->distance = 0;
//         double y = ray_y;
//         double x = ray_x;
//         double dy = sin(data->dir);
//         double dx = cos(data->dir);
//         while (data->map_info->map[(int)y / 40][(int)x / 40] != '1')
//         {
//             my_mlx_pixel_put(data, (int)x, (int)y, 0xFFF00F);
//             x -= dx;
//             y -= dy;
//             data->distance++;
//         }
//         // data->wall_hitx = x;
//         // data->wall_hity = y;
// 		//data->wall_type =  check_v_o((int)y / 40, (int)x / 40);
//         //data->wall_height = wall_hight(data);
//         //get_start_end(data);
// 		//printf("[%d]\n", data->wall_orientation);
//         //draw(data, j);
//         //j--;
//         i += 0.001;
//     }
// }
void ray_create(t_gameworld *data, double ray_y, double ray_x)
{
    double	i = -0.5;
	//int		j = 1999;
    while (i <= 0.5)
    {
		//int hit_vert = 0, hit_horz = 0;
        data->distance = 0;
        double y = ray_y;
        double x = ray_x;
        double dy = cos(data->dir + i);
        double dx = sin(data->dir + i);
        while (data->map_info->map[(int)y / 40][(int)x / 40] != '1')
        {
            my_mlx_pixel_put(data, (int)x, (int)y, 0xFFF00F);
			// if (data->map_info->map[(int)y / 40][(int)(x-dx) / 40] == '1')
			// 	hit_vert = 1;
            // if (data->map_info->map[(int)(y-dy) / 40][(int)x / 40] == '1')
			// 	hit_horz = 1;
            x -= dx;
            y -= dy;
            data->distance++;
        }
		// data->wall_hitx = x;
		// data->wall_hity = y;
		// data->wall_height = wall_hight(data);
		// get_start_end(data);
		//p = that_wall(data, ray_y, ray_x, data->wall_hity, data->wall_hitx);
		// if (hit_horz)
		// 	draw(data, j, 0xFFFFF);
		// else if (hit_vert)
		// 	draw(data, j, 0xFF00FF);
		// else
		// 	draw(data, j, 0xFF00FF);
		//j--;
		// printf("---------------------------------------\n%f\n", data->distance);
		// printf("point of hit: %.1f - %.1f | wall hieght: %f\n", data->wall_hitx, data->wall_hity, data->wall_height);
        i += 0.001;
    }
	//printf("[%d]\n", j);
}
int	ft_moves(int key, t_gameworld *data)
{
	int	y;
	int	x;
    printf("%d\n", key);
	if (key != 119 && key != 115 && key != 65363 && key != 65361)
		return (0);
	realloc_image(data);
	if (key == 115)
	{
        printf("Right\n");
		y = data->map_info->player_y - sin(data->dir - M_PI/2) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / 40][x / 40] != '1')
			data->map_info->player_y -= sin(data->dir- M_PI/2) * data->speed;
		x = data->map_info->player_x + cos(data->dir- M_PI/2) * data->speed;
		y = data->map_info->player_y;
		if (data->map_info->map[y / 40][x / 40] != '1')
			data->map_info->player_x += cos(data->dir- M_PI/2) * data->speed;
	}
	else if (key == 119)
	{
        printf("Left\n");
		y = data->map_info->player_y - sin(data->dir+ M_PI/2) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / 40][x / 40] != '1')
			data->map_info->player_y -= sin(data->dir+ M_PI/2) * data->speed;
		x = data->map_info->player_x + cos(data->dir+ M_PI/2) * data->speed;
		y = data->map_info->player_y;
		if (data->map_info->map[y / 40][x / 40] != '1')
			data->map_info->player_x += cos(data->dir+ M_PI/2) * data->speed;
	}
	else if (key == 65361)
    {
		data->dir+= 0.1;
        printf("Dawr limn\n");
    }
	else if (key == 65363)
    {
		data->dir -= 0.1;
        printf("Dawr Lisr\n");
    }
	draw_elements(data);
	printf("y: %d ==== x: %d\n", data->map_info->player_y, data->map_info->player_x);
	x = 0;
	while (x < 4)
	{
		circleBres(data, x);
		x++;
	}
	ray_create(data, data->map_info->player_y, data->map_info->player_x);
	// advanced_ray_create(data);
	mlx_put_image_to_window(data->connection, data->win,
    data->imageToDraw.img, 0, 0);
	mlx_destroy_image(data->connection, data->imageToDraw.img);
	return (0);
}