/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/26 23:46:42 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	forward_movement(int key, t_gameworld *data)
{
	int	x;
	int	y;

	if (key == 119)
	{
		y = data->map_info->player_y - sin(data->dir + M_PI / 2) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / GRID][x / GRID] != '1')
			data->map_info->player_y -= sin(data->dir + M_PI / 2) * data->speed;
		x = data->map_info->player_x + cos(data->dir + M_PI / 2) * data->speed;
		y = data->map_info->player_y;
		if (data->map_info->map[data->map_info->player_y / GRID][x
			/ GRID] != '1')
			data->map_info->player_x += cos(data->dir + M_PI / 2) * data->speed;
	}
	return (0);
}

int	backward_movement(int key, t_gameworld *data)
{
	int	y;
	int	x;

	if (key == 115)
	{
		y = data->map_info->player_y - sin(data->dir - M_PI / 2) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / GRID][x / GRID] != '1')
			data->map_info->player_y -= sin(data->dir - M_PI / 2) * data->speed;
		x = data->map_info->player_x + cos(data->dir - M_PI / 2) * data->speed;
		y = data->map_info->player_y;
		if (data->map_info->map[data->map_info->player_y / GRID][x
			/ GRID] != '1')
			data->map_info->player_x += cos(data->dir - M_PI / 2) * data->speed;
	}
	return (0);
}

int	right_movement(int key, t_gameworld *data)
{
	int	y;
	int	x;

	if (key == 97)
	{
		y = data->map_info->player_y - sin(data->dir + M_PI) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / GRID][x / GRID] != '1')
			data->map_info->player_y -= sin(data->dir + M_PI) * data->speed;
		x = data->map_info->player_x + cos(data->dir + M_PI) * data->speed;
		y = data->map_info->player_y;
		if (data->map_info->map[data->map_info->player_y / GRID][x
			/ GRID] != '1')
			data->map_info->player_x += cos(data->dir + M_PI) * data->speed;
	}
	return (0);
}

int	left_movement(int key, t_gameworld *data)
{
	int	y;
	int	x;

	if (key == 100)
	{
		y = data->map_info->player_y - sin(data->dir) * data->speed;
		x = data->map_info->player_x;
		if (data->map_info->map[y / GRID][x / GRID] != '1')
		{
			y = data->map_info->player_y;
			data->map_info->player_y -= sin(data->dir) * data->speed;
		}
		else
			y = data->map_info->player_y;
		x = data->map_info->player_x + cos(data->dir) * data->speed;
		if (data->map_info->map[y / GRID][x / GRID] != '1')
			data->map_info->player_x += cos(data->dir) * data->speed;
	}
	return (0);
}

int	ft_moves(int key, t_gameworld *data)
{
	if (key == 65293 && data->checkenter == 0)
		data->checkenter = 1;
	if (key == 65307)
		exit(0);
	if (data->checkenter == 1)
	{
		if (key != 65363 && key != 65361 && key != 119 && key != 115
			&& key != 65293 && key != 97 && key != 100)
			return (0);
		realloc_image(data);
		backward_movement(key, data);
		forward_movement(key, data);
		right_movement(key, data);
		left_movement(key, data);
		if (key == 65361)
			data->dir += 0.1;
		else if (key == 65363)
			data->dir -= 0.1;
		draw_ray(data, data->map_info->player_y, data->map_info->player_x,
			WIN_WIDTH);
		mlx_put_image_to_window(data->connection, data->win,
			data->imagetodraw.img, 0, 0);
		mlx_destroy_image(data->connection, data->imagetodraw.img);
	}
	return (0);
}
