/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/17 22:35:50 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

void    realloc_image(t_gameworld *world)
{
	world->imageToDraw.img = mlx_new_image(world->connection, 
    WIN_WIDTH, WIN_HIGHT);
    world->imageToDraw.addr = mlx_get_data_addr(world->imageToDraw.img,
		&world->imageToDraw.bits_per_pixel, &world->imageToDraw.line_length,
		&world->imageToDraw.endian);
}

double	wall_hight(t_gameworld *data, double ray)
{
	double	height = 0;
	double	real_dis = 0;
	
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

int get_texture_color(t_image *texture, int x, int y)
{
    int pixel_position;
    unsigned int color;

    if (x < 0 || y < 0 || x >= texture->w || y >= texture->h)
        return (0);
    pixel_position = y * texture->line_length + x * (texture->bits_per_pixel / 8);
    color = *(unsigned int *)(texture->addr + pixel_position);
    return (color);
}

int createRGB(int r, int g, int b)
{   
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void	draw(t_gameworld *data, int j, int color, int hit_horz, int hit_vert)
{
	int i;
	double l;
	double m;
	int a = 0;

	i = data->start;
	int k = 0;
	if (data->orientation == NORTH)
		a = NORTH;
	if (data->orientation == SOUTH)
		a = SOUTH;
	if (data->orientation == EAST)
		a = EAST;
	if (data->orientation == WEST)
		a = WEST;
	if (hit_vert)
        data->t[a].x = (int)data->wall_hity % (int)data->t[a].w;
    else if (hit_horz)
	{
        data->t[a].x = (int)data->wall_hitx % (int)data->t[a].w;
	}
	data->t[a].y = 0;
	while (k < data->start)
	{
		data->map_info->celling.flag = createRGB(data->map_info->celling.r, data->map_info->celling.g, data->map_info->celling.b);
		my_mlx_pixel_put(data, j, k, data->map_info->celling.flag);
		k++;
	}
	data->t[a].y = 0;
	while (i < data->end)
	{
		l = (double)data->t[a].h / data->wall_height;
		m = data->t[a].y;
		if (data->wall_height > WIN_HIGHT)
        	data->t[a].y += l * (data->wall_height - WIN_HIGHT) / 2;
		color = get_texture_color(&(data->t[a]), (int)data->t[a].x, (int)data->t[a].y);
		data->t[a].y = m;
		my_mlx_pixel_put(data, j, i, color);
		i++;
		k++;
		data->t[a].y += l;
	}
	while (k >= data->end && k < WIN_HIGHT)
	{
		data->map_info->floor.flag = createRGB(data->map_info->floor.r, data->map_info->floor.g, data->map_info->floor.b);
		my_mlx_pixel_put(data, j, k, data->map_info->floor.flag);
		k++;
	}
}

double ft_distance (double px, double py, double wx, double wy)
{
	double dx;
	double dy;

	dx = px - wx;
	dy = py - wy;
	return (sqrt(dx * dx + dy * dy));
}

int ft_orientation(int hit_vert, int hit_horz, double i, t_gameworld *data)
{
	double rayangle = data->dir + i;
	if (hit_horz && cos(rayangle) < 0)
		return(WEST);
	if (hit_horz && cos(rayangle) > 0)
		return(EAST);
	if (hit_vert && sin(rayangle) < 0)
		return(SOUTH);
	if (hit_vert && sin(rayangle) > 0)
		return(NORTH);
	return (0);
}

void ray_create(t_gameworld *data, double ray_y, double ray_x)
{
    double	i = -M_PI / 6;
	int		j = WIN_WIDTH;
	double increment;
	int		hit_vert;
	int		hit_horz;
	int c = 0;

	increment = (M_PI / 3) / WIN_WIDTH;
    while (i <= M_PI / 6)
    {
        data->distance = 0;
        double y = ray_y;
        double x = ray_x;
        double dy = cos(data->dir + i);
        double dx = sin(data->dir + i);
		hit_vert = 0;
		hit_horz = 0;
        while (data->map_info->map[(int)(y / GRID)][(int)(x / GRID)] != '1')
        {
			
			if (data->map_info->map[(int)(y / GRID)][(int)((x-dx) / GRID)] == '1')
				hit_vert = 1;
            if (data->map_info->map[(int)((y-dy) / GRID)][(int)(x / GRID)] == '1')
				hit_horz = 1;
            x -= dx;
            y -= dy;
        }
		data->wall_hitx = x;
		data->wall_hity = y;
		double dis;
		dis = ft_distance(ray_x, ray_y, x, y);
		data->distance = dis;
		data->orientation = ft_orientation(hit_vert, hit_horz, i, data);
		data->wall_height = wall_hight(data, i);
		get_start_end(data);
		draw(data, j, 0xFF00FF, hit_horz, hit_vert);
		j--;
		c++;
        i += increment;
    }
}

int	ft_moves(int key, t_gameworld *data)
{
	int	y;
	int	x;

	if (key == 65293 && data->checkEnter == 0)
		data->checkEnter = 1;
	if (key == 65307)
		exit(0);
	if (data->checkEnter == 1)
	{
		if (key != 65363 && key != 65361 && key != 119 && key != 115 && key != 65293 && key != 97 && key != 100)
			return (0);
		realloc_image(data);
		if (key == 115)
		{
			// - sin(data->dir - M_PI/2) = cos(data->dir)
			y = data->map_info->player_y - sin(data->dir - M_PI/2) * data->speed;
			x = data->map_info->player_x;
			if (data->map_info->map[y / GRID][x / GRID] != '1')
			//cos(data->dir- M_PI/2) = sin(data->dir)
				data->map_info->player_y -= sin(data->dir - M_PI / 2) * data->speed;
			x = data->map_info->player_x + cos(data->dir- M_PI/2) * data->speed;
			y = data->map_info->player_y;
			if (data->map_info->map[data->map_info->player_y / GRID][x / GRID] != '1')
				data->map_info->player_x += cos(data->dir- M_PI/2) * data->speed;
		}
		else if (key == 119)
		{
			y = data->map_info->player_y - sin(data->dir + M_PI/2) * data->speed;
			x = data->map_info->player_x;
			if (data->map_info->map[y / GRID][x / GRID] != '1')
				data->map_info->player_y -= sin(data->dir+ M_PI/2) * data->speed;
			x = data->map_info->player_x + cos(data->dir+ M_PI/2) * data->speed;
			y = data->map_info->player_y;
			if (data->map_info->map[data->map_info->player_y / GRID][x / GRID] != '1')
				data->map_info->player_x += cos(data->dir+ M_PI/2) * data->speed;
		}
		else if (key == 97)
		{
			y = data->map_info->player_y - sin(data->dir + M_PI ) * data->speed;
			x = data->map_info->player_x;
			if (data->map_info->map[y / GRID][x / GRID] != '1')
				data->map_info->player_y -= sin(data->dir + M_PI ) * data->speed;
			x = data->map_info->player_x + cos(data->dir + M_PI) * data->speed;
			y = data->map_info->player_y;
			if (data->map_info->map[data->map_info->player_y / GRID][x / GRID] != '1')
				data->map_info->player_x += cos(data->dir + M_PI) * data->speed;
		}
		else if (key == 100)
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
		else if (key == 65361)
			data->dir+= 0.1;
		else if (key == 65363)
			data->dir -= 0.1;
		ray_create(data, data->map_info->player_y, data->map_info->player_x);
		mlx_put_image_to_window(data->connection, data->win,
    	data->imageToDraw.img, 0, 0);
		mlx_destroy_image(data->connection, data->imageToDraw.img);
	}
	return (0);
}

int        mouse_motion_hook(int x, int y, void *param)
{
        t_gameworld       *game;

        game = (t_gameworld*)param;
        if (x <= WIN_WIDTH && x >= 0 && y <= WIN_HIGHT && y >= 0)
        {
                if (game->mouse_x > x)
                        game->dir += x * 0.00003;
                else
                        game->dir += -x * 0.00003;
        }
        game->mouse_x = x;
        game->mouse_y = y;
		realloc_image(game);
		ray_create(game, game->map_info->player_y, game->map_info->player_x);
		mlx_put_image_to_window(game->connection, game->win,
    	game->imageToDraw.img, 0, 0);
		mlx_destroy_image(game->connection, game->imageToDraw.img);
        return (0);
}
