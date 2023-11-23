/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/16 03:21:50 by lahamoun         ###   ########.fr       */
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
    data->speed = 15;
}

// void	draw_hight(t_gameworld *data)
// {
// 	int	i;
// 	int	j;
// 	int	fourty;

// 	i = 0;
// 	fourty = 40;
// 	while(i < data->h - 1)
// 	{
// 		j = 0;
// 		while (j < data->w * 40)
// 		{
// 			my_mlx_pixel_put(data, j, fourty, 0x00FF00);
// 			j++;
// 		}
// 		fourty+=40;
// 		i++;
// 	}
// }

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
	// draw_hight(data);
	// draw_width(data);

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
void texture_init (t_gameworld *game, t_image *texture, char* path)
{
        texture->img = mlx_xpm_file_to_image(game->connection, path, &(texture->w), &(texture->h));
        if (!texture->img)
        {
			if (msg_er("texture not found"))
            	exit (0);
        }
        texture->addr = mlx_get_data_addr(texture->img, &(texture->bits_per_pixel), &(texture->line_length), &(texture->endian));
        texture->x = 0;
        texture->y = 0;
}
void	welcomer(t_gameworld *world)
{
	//unsigned long i = 0;
	mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF, "Welcome To The Game...");
	mlx_string_put(world->connection, world->win, 475, 510, 0xF509FF, "Press Enter To Start");
	// while (i < 56746745675)
	// {
	// 	mlx_string_put(world->connection, world->win, , 475, 0xF509FF, "Welcome To The Game");
	// }
	// mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF, "Welcome To The Game");
	// mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF, "Welcome To The Game");
	// mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF, "Welcome To The Game");

}

void image_init(t_gameworld *game)
{
	texture_init(game, &(game->t[NORTH]), "./texture/north_texture.xpm");
	texture_init(game, &(game->t[SOUTH]), "./texture/south_texture.xpm");
	texture_init(game, &(game->t[EAST]), "./texture/east_texture.xpm");
	texture_init(game, &(game->t[WEST]), "./texture/west_texture.xpm");
}

void    raycast(t_gameworld *world)
{
	world->checkEnter = 0;
    map_size(world);
    get_dir(world);
    //get_pos(world);
    world->map_info->player_x *= 40;
    world->map_info->player_y *= 40;
    printf("%c == %f\n", world->map_info->pov, world->dir);
    printf("Map Demon-> h: %d ==> w: %d\n", world->h, world->w);
    world->connection = mlx_init();
    // world->win = mlx_new_window(world->connection, world->w * 40,
    //      world->h * 40, "cub3D");
	image_init(world);
	world->win = mlx_new_window(world->connection, WIN_WIDTH,
		WIN_HIGHT, "cub3D");
	welcomer(world);
    for (int i = 0; i < world->h; i++)
    {
        printf("[%s]\n", world->map_info->map[i]);
    }
    mlx_hook(world->win, 2, 1L<<0, ft_moves, world);
	mlx_hook(world->win, 17, 1L<<17, (void *)exit, world);
    mlx_loop(world->connection);
}