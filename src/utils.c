/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 21:36:24 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/26 23:58:58 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	msg_er(char *msg)
{
	printf("\033[1;31mError:\nCub3D:\033[0;0m %s\n", msg);
	return (1);
}

int	find_biggest_line(char **str)
{
	int	i;
	int	max;
	int	j;

	i = 0;
	max = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
			j++;
		if (j > max)
			max = j;
		i++;
	}
	return (max);
}

void	fill_x(int *i, int *k, t_map *map, char **str)
{
	while ((*i) < map->map_len)
	{
		map->map_clone[(*i) + 1] = my_malloc(sizeof(char) * (map->max_line
					+ 3));
		map->map_clone[(*i) + 1][0] = 'x';
		map->j = 0;
		(*k) = 1;
		while (str[(*i)][map->j])
		{
			if (str[(*i)][map->j] == ' ')
				map->map_clone[(*i) + 1][(*k)] = 'x';
			else
				map->map_clone[(*i) + 1][(*k)] = str[(*i)][map->j];
			map->j++;
			(*k)++;
		}
		while ((*k) <= map->max_line + 1)
		{
			map->map_clone[(*i) + 1][(*k)] = 'x';
			(*k)++;
		}
		map->map_clone[(*i) + 1][(*k)] = '\0';
		(*i)++;
	}
}

int	map_len(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	get_map(char **str, t_map *map)
{
	int	i;

	i = 0;
	map->k = 0;
	map->max_line = find_biggest_line(str);
	map->map_len = map_len(str);
	map->map_clone = (char **)my_malloc(sizeof(char *) * (map->map_len + 3));
	map->map_clone[0] = (char *)my_malloc(sizeof(char) * (map->max_line + 3));
	while (map->k <= map->max_line + 1)
	{
		map->map_clone[0][map->k] = 'x';
		map->k++;
	}
	map->map_clone[0][map->k] = '\0';
	fill_x(&i, &map->k, map, str);
	map->map_clone[i + 1] = (char *)my_malloc(sizeof(char) * (map->max_line
				+ 3));
	map->k = 0;
	while (map->k <= map->max_line + 1)
	{
		map->map_clone[i + 1][map->k] = 'x';
		map->k++;
	}
	map->map_clone[i + 1][map->k] = '\0';
	map->map_clone[i + 2] = NULL;
}
