/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 03:51:10 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/27 00:01:57 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	getmaxcolumns(char **map)
{
	int	max_columns;
	int	i;
	int	len;

	max_columns = 0;
	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_columns)
			max_columns = len;
		i++;
	}
	return (max_columns);
}

int	getmapheight(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	calculatetilesize(char **map)
{
	int	map_width;
	int	map_height;
	int	tile_size_width;
	int	tile_size_height;

	map_width = getmaxcolumns(map);
	map_height = getmapheight(map);
	tile_size_width = SCREEN_WIDTH / map_width;
	tile_size_height = SCREEN_HEIGHT / map_height;
	if (tile_size_width < tile_size_height)
		return (tile_size_width);
	else
		return (tile_size_height);
}

int	mouse_motion_hook(int x, int y, void *param)
{
	t_gameworld	*game;

	game = (t_gameworld *)param;
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
	draw_ray(game, game->map_info->player_y, game->map_info->player_x,
		WIN_WIDTH);
	mlx_put_image_to_window(game->connection, game->win, game->imagetodraw.img,
		0, 0);
	mlx_destroy_image(game->connection, game->imagetodraw.img);
	return (0);
}
