/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:02:46 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/28 22:52:33 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_dirs(t_map *map, char *str, char flag)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			msg_er("Texture Error");
			exit(1);
		}
		i++;
	}
	if (flag == 'N')
		map->n_path = ft_strdup(str + j);
	if (flag == 'S')
		map->s_path = ft_strdup(str + j);
	if (flag == 'E')
		map->e_path = ft_strdup(str + j);
	if (flag == 'W')
		map->w_path = ft_strdup(str + j);
}

void	directions(t_map *map, char **str, int *i)
{
	if (!ft_strncmp(str[(*i)], "NO", 2))
		get_dirs(map, str[(*i)] + 2, 'N');
	else if (!ft_strncmp(str[(*i)], "SO", 2))
		get_dirs(map, str[(*i)] + 2, 'S');
	else if (!ft_strncmp(str[(*i)], "WE", 2))
		get_dirs(map, str[(*i)] + 2, 'W');
	else if (!ft_strncmp(str[(*i)], "EA", 2))
		get_dirs(map, str[(*i)] + 2, 'E');
}

void	get_colors(char **str, t_map *map, int *i)
{
	if (!ft_strncmp(str[(*i)], "F", 1))
	{
		if (map->f_color)
		{
			msg_er("Invalid color");
			exit(1);
		}
		map->f_color = ft_strdup(str[(*i)] + 1);
	}
	else if (!ft_strncmp(str[(*i)], "C", 1))
	{
		if (map->c_color)
		{
			msg_er("Invalid color");
			exit(1);
		}
		map->c_color = ft_strdup(str[(*i)] + 1);
	}
	if (!str[(*i) + 1])
	{
		msg_er("Invalid map");
		exit(1);
	}
}

void	map_fill(char **str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_strncmp(str[(i)], "NO", 2) || !ft_strncmp(str[(i)], "SO", 2)
			|| !ft_strncmp(str[(i)], "WE", 2) || !ft_strncmp(str[(i)], "EA", 2))
			directions(map, str, &i);
		else if (!ft_strncmp(str[(i)], "F", 1) || !ft_strncmp(str[(i)], "C", 1))
			get_colors(str, map, &i);
		else
		{
			map->map = &str[i];
			get_map(&str[i], map);
			break ;
		}
		i++;
	}
	if (check_for_colors(map))
		exit(1);
}
