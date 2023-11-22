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
    // world->imageToDraw.img = mlx_new_image(world->connection, 
    // world->w * 40, world->h * 40);
	world->imageToDraw.img = mlx_new_image(world->connection, 
    WIN_WIDTH, WIN_HIGHT);
    world->imageToDraw.addr = mlx_get_data_addr(world->imageToDraw.img,
		&world->imageToDraw.bits_per_pixel, &world->imageToDraw.line_length,
		&world->imageToDraw.endian);
}

double	wall_hight(t_gameworld *data)
{
	double	height;
	double	real_dis;
	
	real_dis = ((double)WIN_WIDTH / 2) / tan(0.5);
	//real_dis = ((data->w * 40) / 2) / tan(0.5);
	height = (40 * real_dis) / data->distance;
	return (height);
}

void	get_start_end(t_gameworld *data)
{
	data->start = (double)WIN_HIGHT / 2 - data->wall_height / 2;
	//data->start = (data->h * 40) / 2 - data->wall_height / 2;
	data->end = (double)WIN_HIGHT / 2 + data->wall_height / 2;
	//data->end = (data->h * 40) / 2 + data->wall_height / 2;
	if (data->start < 0)
		data->start = 0;
	if (data->end >= WIN_HIGHT)
		data->end = WIN_HIGHT - 1;
	// if (data->end >= data->h * 40)
	// 	data->end = data->h * 40 - 1;
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
        	data->t[a].x = (int)data->wall_hitx % (int)data->t[a].w;
	if (data->t[a].x >= data->t[a].w)
				data->t[a].x -= data->t[a].w;
	data->t[a].y = 0;
	
	while (k < data->start)
	{
		my_mlx_pixel_put(data, j, k, 0x85C1E9);
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
		//printf("x = %f, y = %f\n", t->x, t->y);
	}
}

double ft_distance (double px, double py, double wx, double wy)
{
	double dx;
	double dy;

	dx = wx - wx;
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
}

void ray_create(t_gameworld *data, double ray_y, double ray_x)
{
    double	i = -M_PI / 6;
	int		j = WIN_WIDTH;
	double increment;
	int		hit_vert;
	int		hit_horz;
	double	k;
	t_image t;


	texture_init(data, &t, "./src/texture.xpm");
	increment = (M_PI / 3) / j;
    while (i <= M_PI / 6)
    {
        data->distance = 0;
        double y = ray_y;
        double x = ray_x;
        double dy = cos(data->dir + i);
        double dx = sin(data->dir + i);
		hit_vert = 0; 
		hit_horz = 0;
        while (data->map_info->map[(int)y / 40][(int)x / 40] != '1')
        {
            //my_mlx_pixel_put(data, (int)x, (int)y, 0xFFF00F);
			if (data->map_info->map[(int)y / 40][(int)(x-dx) / 40] == '1')
				hit_vert = 1;
            if (data->map_info->map[(int)(y-dy) / 40][(int)x / 40] == '1')
				hit_horz = 1;
            x -= dx;
            y -= dy;
            data->distance++;
        }
		//data->distance = distance(ray_x, ray_y, x, y);
		double angleDifference = fabs(data->dir - (data->dir + i)); 
    	if (angleDifference < M_PI / 2)
        	data->distance = data->distance * cos(angleDifference);
    	else
        	data->distance = data->distance * cos(M_PI - angleDifference);
		data->orientation = ft_orientation(hit_vert, hit_horz, i, data);
		data->wall_hitx = x;
		data->wall_hity = y;
		data->wall_height = wall_hight(data);
		//data->wall_height = (int)((40 * WIN_HIGHT) / data->distance);
		get_start_end(data);
		//k = (double)t.h / data->wall_height;
		// if (hit_vert)
        // 	t.x = (int)data->wall_hitx % (int)t.w;
    	// else if (hit_horz)
        // 	t.x = (int)data->wall_hity % (int)t.w;
		// if (t.x >= t.w)
		// 		t.x -= t.w;
		//if (hit_horz)
		//	draw(data, j, 0xFFFFF);
		//else if (hit_vert)
		//	draw(data, j, 0xFF00FF);
		//else
		draw(data, j, 0xFF00FF, hit_horz, hit_vert);
		//t.y += k;
		j--;
        i += increment;
    }
}
int	ft_moves(int key, t_gameworld *data)
{
	int	y;
	int	x;
    printf("%d\n", key);
	if (key == 36 && data->checkEnter == 0)
		data->checkEnter = 1;
	if (key == 65307)
		exit(0);
	if (data->checkEnter == 1)
	{
		if (key != 1 && key != 13 && key != 123 && key != 124 && key != 36)
			return (0);
		realloc_image(data);
		if (key == 13)
		{
    	    printf("Right\n");
			// - sin(data->dir - M_PI/2) = cos(data->dir)
			y = data->map_info->player_y - sin(data->dir - M_PI/2) * data->speed;
			x = data->map_info->player_x;
			if (data->map_info->map[y / 40][x / 40] != '1')
			//cos(data->dir- M_PI/2) = sin(data->dir)
				data->map_info->player_y -= sin(data->dir- M_PI/2) * data->speed;
			x = data->map_info->player_x + cos(data->dir- M_PI/2) * data->speed;
			y = data->map_info->player_y;
			if (data->map_info->map[y / 40][x / 40] != '1')
				data->map_info->player_x += cos(data->dir- M_PI/2) * data->speed;
		}
		else if (key == 1)
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
		else if (key == 124)
    	{
			data->dir+= 0.1;
    	    printf("Dawr limn\n");
    	}
		else if (key == 123)
    	{
			data->dir -= 0.1;
    	    printf("Dawr Lisr\n");
    	}
		//draw_elements(data);
		printf("y: %d ==== x: %d\n", data->map_info->player_y, data->map_info->player_x);
		// x = 0;
		// while (x < 4)
		// {
		// 	circleBres(data, x);
		// 	x++;
		// }
		ray_create(data, data->map_info->player_y, data->map_info->player_x);
		mlx_put_image_to_window(data->connection, data->win,
    	data->imageToDraw.img, 0, 0);
		mlx_destroy_image(data->connection, data->imageToDraw.img);
	}
	return (0);
}
