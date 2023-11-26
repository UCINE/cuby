/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:46:21 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/26 23:46:45 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	wall_hight(t_gameworld *data, double ray)
{
	double	height;
	double	real_dis;

	height = 0;
	real_dis = 0;
	real_dis = data->distance * cos(ray);
	height = (GRID * WIN_HIGHT) / real_dis;
	return (height);
}

void	get_start_end(t_gameworld *data)
{
	data->start = (int)((WIN_HIGHT / 2) - (data->wall_height / 2));
	data->end = (int)((WIN_HIGHT / 2) + (data->wall_height / 2));
	if (data->start < 0)
		data->start = 0;
	if (data->end >= WIN_HIGHT)
		data->end = WIN_HIGHT - 1;
}

int	get_texture_color(t_image *texture, int x, int y)
{
	int				pixel_position;
	unsigned int	color;

	if (x < 0 || y < 0 || x >= texture->w || y >= texture->h)
		return (0);
	pixel_position = y * texture->line_length + x * (texture->bits_per_pixel
			/ 8);
	color = *(unsigned int *)(texture->addr + pixel_position);
	return (color);
}

int	creatergb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	draw_ceiling_and_floor(t_gameworld *data, int j)
{
	int	k;

	k = 0;
	while (k < data->start)
	{
		data->map_info->celling.flag = creatergb(data->map_info->celling.r,
				data->map_info->celling.g, data->map_info->celling.b);
		my_mlx_pixel_put(data, j, k, data->map_info->celling.flag);
		k++;
	}
	k = data->end;
	while (k >= data->end && k < WIN_HIGHT)
	{
		data->map_info->floor.flag = creatergb(data->map_info->floor.r,
				data->map_info->floor.g, data->map_info->floor.b);
		my_mlx_pixel_put(data, j, k, data->map_info->floor.flag);
		k++;
	}
}
