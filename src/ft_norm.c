/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:44:13 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/26 23:50:54 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_s(t_gameworld *data, int j, int color)
{
	int		i;
	int		a;
	double	l;
	double	m;

	i = data->start;
	a = data->current_texture_index;
	while (i < data->end)
	{
		l = (double)data->t[a].h / data->wall_height;
		m = data->t[a].y;
		if (data->wall_height > WIN_HIGHT)
			data->t[a].y += l * (data->wall_height - WIN_HIGHT) / 2;
		color = get_texture_color(&(data->t[a]), (int)data->t[a].x,
				(int)data->t[a].y);
		data->t[a].y = m;
		my_mlx_pixel_put(data, j, i, color);
		i++;
		data->t[a].y += l;
	}
}

void	setup_wall_parameters(t_gameworld *data, t_ray *ray)
{
	int	a;

	a = 0;
	if (data->orientation == NORTH)
		a = NORTH;
	else if (data->orientation == SOUTH)
		a = SOUTH;
	else if (data->orientation == EAST)
		a = EAST;
	else if (data->orientation == WEST)
		a = WEST;
	if (ray->hit_vert)
		data->t[a].x = (int)data->wall_hity % (int)data->t[a].w;
	else if (ray->hit_horz)
		data->t[a].x = (int)data->wall_hitx % (int)data->t[a].w;
	data->t[a].y = 0;
	data->current_texture_index = a;
}

void	draw_walls(t_gameworld *data, int j, int color, t_ray *ray)
{
	setup_wall_parameters(data, ray);
	draw_wall_s(data, j, color);
}

double	ft_distance(double px, double py, double wx, double wy)
{
	double	dx;
	double	dy;

	dx = px - wx;
	dy = py - wy;
	return (sqrt(dx * dx + dy * dy));
}

int	orien(int hit_vert, int hit_horz, double i, t_gameworld *data)
{
	double	rayangle;

	rayangle = data->dir + i;
	if (hit_horz && cos(rayangle) < 0)
		return (WEST);
	if (hit_horz && cos(rayangle) > 0)
		return (EAST);
	if (hit_vert && sin(rayangle) < 0)
		return (SOUTH);
	if (hit_vert && sin(rayangle) > 0)
		return (NORTH);
	return (0);
}
