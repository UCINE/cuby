/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 23:28:31 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/26 03:42:31 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_textures(t_map *map)
{
	if (!map->n_path)
		return msg_er("Invalid texture");
	if (!map->e_path)
		return msg_er("Invalid texture");
	if (!map->s_path)
		return msg_er("Invalid texture");
	if (!map->w_path)
		return msg_er("Invalid texture");
	return (0);
}

int	check_for_colors(t_map *map)
{
	if (!map->f_color)
		return msg_er("Invalid color");
	if (!map->c_color)
		return msg_er("Invalid color");
	if ((check_colors(map->f_color, &map->floor)
		|| check_colors(map->c_color, &map->celling)))
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
			if (charset == 'N' || charset == 'S'
				|| charset == 'E' || charset == 'W')
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

int	player_angle(char pov)
{
	if (pov == 'N')
		return (1);
	else if (pov == 'E')
		return (2);
	else if (pov == 'W')
		return (3);
	else if (pov == 'S')
		return (4);
	return (0);
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;
	int	save;

	j = 0;
	i = 0;
	save = 0;
	while(map->map[i])
	{
		j = 0;
		while(map->map[i][j])
		{
			save = check_charset(map, map->map[i][j], "01NSEW \t");
			if (!save)
				return msg_er("Invalid charset");
			else if (save == 2)
			{
				map->pov = player_angle(map->map[i][j]);
				map->player_y = i;
				map->player_x = j;
			}
			j++;
		}
		i++;
	}
	if (map->player != 1)
		return msg_er("Invalid player");
	return (0);
}

int	check_ups(t_map *map, int i, int j)
{
	int	k;

	k = i - 1;
	if (k > 0 && map->map_clone[k][j] != '1' && map->map_clone[k][j] != 'x')
		return msg_er("Unclosed Wall");
	k = i + 1;
	if (k < map->map_len && map->map_clone[k][j] != '1' && map->map_clone[k][j] != 'x'
		&& map->map_clone[k][j] != '0')
		return msg_er("Unclosed Wall");
	return (0);
}

int	check_sides(t_map *map, int j, int i)
{
	int	k;

	k = j - 1;
	if (k > 0 && map->map_clone[i][k] != '1' && map->map_clone[i][k] != 'x')	
		return msg_er("Unclosed Wall");
	k = j + 1;
	if (k > 0 && k < map->max_line && map->map_clone[i][k] != '1' && map->map_clone[i][k] != 'x'
		&& map->map_clone[i][k] != '0')
		return msg_er("Unclosed Wall");
	return (0);
}

int	map_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (check_for_colors(map) || check_for_textures(map) || check_chars(map))
		return (1);
	while(map->map_clone[i])
	{
		j = 0;
		while(map->map_clone[i][j])
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
