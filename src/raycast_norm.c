/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:39:29 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/29 00:58:36 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	welcomer(t_gameworld *world)
{
	mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF,
		"Welcome To The Game...");
	mlx_string_put(world->connection, world->win, 475, 510, 0xF509FF,
		"Press Enter To Start");
}

void	calculate_ray_intersection(t_gameworld *data, t_ray *ray)
{
	double	y;
	double	x;
	double	dy;
	double	dx;

	y = ray->p_y;
	x = ray->p_x;
	ray->hit_vert = 0;
	ray->hit_horz = 0;
	dy = cos(data->dir + ray->angle) / 15;
	dx = sin(data->dir + ray->angle) / 15;
	while (data->map_info->map[(int)(y / GRID)][(int)(x / GRID)] != '1')
	{
		if (data->map_info->map[(int)(y / GRID)][(int)((x - dx) / GRID)] == '1')
			ray->hit_vert = 1;
		if (data->map_info->map[(int)((y - dy) / GRID)][(int)(x / GRID)] == '1')
			ray->hit_horz = 1;
		x -= dx;
		y -= dy;
	}
	data->wall_hitx = x;
	data->wall_hity = y;
	data->distance = ft_distance(ray->p_x, ray->p_y, x, y);
	data->orientation = orien(ray->hit_vert, ray->hit_horz, ray->angle, data);
	data->wall_height = wall_hight(data, ray->angle);
}

void	draw(t_gameworld *data, int j, int color, t_ray ray)
{
	draw_ceiling_and_floor(data, j);
	draw_walls(data, j, color, &ray);
}

void	draw_ray(t_gameworld *data, double ray_y, double ray_x, int j)
{
	t_ray	ray;
	double	increment;

	increment = (M_PI / 3) / WIN_WIDTH;
	ray.p_y = ray_y;
	ray.p_x = ray_x;
	ray.angle = -M_PI / 6;
	while (ray.angle <= M_PI / 6)
	{
		calculate_ray_intersection(data, &ray);
		get_start_end(data);
		draw(data, j, 0xFFFFFF, ray);
		j--;
		ray.angle += increment;
	}
}

void	realloc_image(t_gameworld *world)
{
	world->imagetodraw.img = mlx_new_image(world->connection, WIN_WIDTH,
			WIN_HIGHT);
	world->imagetodraw.addr = mlx_get_data_addr(world->imagetodraw.img,
			&world->imagetodraw.bits_per_pixel, &world->imagetodraw.line_length,
			&world->imagetodraw.endian);
}
