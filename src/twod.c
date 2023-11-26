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
    data->speed = 10;
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
	mlx_string_put(world->connection, world->win, 475, 475, 0xF509FF, "Welcome To The Game...");
	mlx_string_put(world->connection, world->win, 475, 510, 0xF509FF, "Press Enter To Start");
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
    get_dir(world);
    world->map_info->player_x *= 40;
    world->map_info->player_y *= 40;
	world->mouse_x = 0;
	world->mouse_y = 0;
    printf("%c == %f\n", world->map_info->pov, world->dir);
    world->connection = mlx_init();
	image_init(world);
	world->win = mlx_new_window(world->connection, WIN_WIDTH,
		WIN_HIGHT, "cub3D");
	welcomer(world);
    mlx_hook(world->win, 2, 1L<<0, ft_moves, world);
	mlx_hook(world->win, 17, 1L<<17, (void *)exit, world);
    mlx_loop(world->connection);
}