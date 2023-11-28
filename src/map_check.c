/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:28:31 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/29 00:40:13 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_colors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map->f_color)
		return (msg_er("Invalid color"));
	if (!map->c_color)
		return (msg_er("Invalid color"));
	if (check_colors(map->f_color, &map->floor, i, j)
		|| check_rgb(&map->floor))
		return (1);
	if (check_colors(map->c_color, &map->celling, i, j)
		|| check_rgb(&map->celling))
		return (1);
	return (0);
}

int	check_charset(t_map *map, char charset, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == charset || charset == '\t')
		{
			if (charset == 'N' || charset == 'S' || charset == 'E'
				|| charset == 'W')
			{
				map->player++;
				return (2);
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_chars(t_map *map, int i, int j)
{
	int	save;

	save = 0;
	while (map->map[i])
	{
		j = 0;
		if (map->map[i][j] == '\n')
			return (msg_er("Invalid map"));
		while (map->map[i][j])
		{
			save = check_charset(map, map->map[i][j], "01NSEW ");
			if (!save)
				return (msg_er("Invalid charset"));
			else if (save == 2)
			{
				map->player_y = i;
				map->player_x = j;
			}
			j++;
		}
		i++;
	}
	if (map->player != 1)
		return (msg_er("Invalid player"));
	return (0);
}

int	map_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_chars(map, i, j))
		return (1);
	while (map->map_clone[i])
	{
		j = 0;
		while (map->map_clone[i][j])
		{
			if (map->map_clone[i][j] == 'x')
			{
				if (check_sides(map, j, i))
					return (1);
				if (check_ups(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
