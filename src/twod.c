/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/05 02:46:07 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_gameworld *data, int x, int y, int color)
{
	char	*dst;

	dst = data->imageToDraw.addr
        + (y * data->imageToDraw.line_length + x * (data->imageToDraw.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	get_dir(t_gameworld *data)
{
	if (data->map_info->pov == 'E')
    	data->dir = -M_PI / 2;
	else if (data->map_info->pov == 'S')
	    data->dir = M_PI;
	else if (data->map_info->pov == 'W')
	    data->dir = M_PI / 2;
	else
	    data->dir = 0;
	// data->x_pos = data->player_x * 40 + 20;
	// data->y_pos = data->player_y * 40 + 20;
    data->speed = 10;
}

void	draw_hight(t_gameworld *data)
{
	int	i;
	int	j;
	int	fourty;

	i = 0;
	fourty = 40;
	while(i < data->h - 1)
	{
		j = 0;
		while (j < data->w * 40)
		{
			my_mlx_pixel_put(data, j, fourty, 0x00FF00);
			j++;
		}
		fourty+=40;
		i++;
	}
}

void	draw_width(t_gameworld *data)
{
	int	i;
	int	fourty;
	int	j;

	i = 0;
	fourty = 40;
	while (i < data->w - 1)
	{
		j = 0;
		while (j < data->h * 40)
		{
			my_mlx_pixel_put(data, fourty, j, 0x00FF00);
			j++;
		}
		fourty+=40;
		i++;
	}
}

void	draw_wall_spaces(t_gameworld *data, int pos1, int pos2, char c)
{
	int	i;
	int j;

	i = 1;
	if (c == '1')
	{
		i = 1;
		while (i < 40)
		{
			j = 1;
			while (j < 40)
			{
				my_mlx_pixel_put(data, pos2 * 40 + i, pos1 * 40 + j, 0x000FFF);
				j+=2;
			}
			i+=2;
		}
	}
	else
	{
		while (i < 40)
		{
			j = 1;
			while (j < 40)
			{
				my_mlx_pixel_put(data, pos2 * 40 + i, pos1 * 40 + j, 0x000000);
				j+=2;
			}
			i+=2;
		}
	}
}

void	map_size(t_gameworld *data)
{
	data->h = 0;
	while (data->map_info->map[data->h])
		data->h++;
	data->w = ft_strlen(data->map_info->map[0]);
}

void	draw_elements(t_gameworld *data)
{
	int	i;
	int	j;
	draw_hight(data);
	draw_width(data);

	i = 0;
	while (data->map_info->map[i])
	{
		j = 0;
		while (data->map_info->map[i][j])
		{
			draw_wall_spaces(data, i, j, data->map_info->map[i][j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->connection, data->win,
    data->imageToDraw.img, 0, 0);
}

// void    get_pos(t_gameworld *world)
// {
//     int i = 0;
//     while (world->map_info->map[i])
//     {
//         int j = 0;
//         while (world->map_info->map[i][j])
//         {
//             if (world->map_info->map[i][j] == 'W'
//                 || world->map_info->map[i][j] == 'N' || world->map_info->map[i][j] == 'E'
//                 || world->map_info->map[i][j] == 'S')
//             {
//                 world->player_y = (float)i;
//                 world->player_x = (float)j;
//                 return ;
//             }
//             j++;
//         }
//         i++;
//     }
// }

void    raycast(t_gameworld *world)
{
    map_size(world);
    get_dir(world);
    //get_pos(world);
    world->map_info->player_x *= 40;
    world->map_info->player_y *= 40;
    printf("%c == %f\n", world->map_info->pov, world->dir);
    printf("Map Demon-> h: %d ==> w: %d\n", world->h, world->w);
    world->connection = mlx_init();
    world->win = mlx_new_window(world->connection, world->w * 40,
         world->h * 40, "cub3D");
    for (int i = 0; i < world->h; i++)
    {
        printf("[%s]\n", world->map_info->map[i]);
    }
    //draw_elements(world);
    mlx_hook(world->win, 2, 1L<<0, ft_moves, world);
    mlx_loop(world->connection);
}