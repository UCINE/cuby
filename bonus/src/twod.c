/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   twod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/29 01:00:46 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_gameworld *data, int x, int y, int color)
{
	char	*dst;

	dst = data->imagetodraw.addr + (y * data->imagetodraw.line_length + x
			* (data->imagetodraw.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	texture_init(t_gameworld *game, t_image *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->connection, path, &(texture->w),
			&(texture->h));
	if (!texture->img)
	{
		msg_er("texture not found");
		exit(0);
	}
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bits_per_pixel),
			&(texture->line_length), &(texture->endian));
	texture->x = 0;
	texture->y = 0;
}

void	image_init(t_gameworld *game)
{
	texture_init(game, &(game->t[NORTH]), game->map_info->n_path);
	texture_init(game, &(game->t[SOUTH]), game->map_info->s_path);
	texture_init(game, &(game->t[EAST]), game->map_info->e_path);
	texture_init(game, &(game->t[WEST]), game->map_info->w_path);
}

void	raycast(t_gameworld *world)
{
	world->checkenter = 0;
	get_dir(world);
	world->map_info->player_x *= 40;
	world->map_info->player_y *= 40;
	world->mouse_x = 0;
	world->mouse_y = 0;
	world->connection = mlx_init();
	image_init(world);
	world->win = mlx_new_window(world->connection, WIN_WIDTH, WIN_HIGHT,
			"cub3D");
	welcomer(world);
	mlx_hook(world->win, 2, 1L << 0, ft_moves, world);
	mlx_hook(world->win, 6, 1L << 6, mouse_motion_hook, world);
	mlx_hook(world->win, 17, 1L << 17, (void *)exit, world);
	mlx_loop(world->connection);
}
