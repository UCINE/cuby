/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 03:02:46 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/12 11:47:41 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	directions(t_map *map, char **str, int *i)
{
	if (!ft_strncmp(str[(*i)], "NO", 2))
		map->n_path = ft_strdup(str[(*i)] + 2);
	else if (!ft_strncmp(str[(*i)], "SO", 2))
		map->s_path = ft_strdup(str[(*i)] + 2);
	else if (!ft_strncmp(str[(*i)], "WE", 2))
		map->w_path = ft_strdup(str[(*i)] + 2);
	else if (!ft_strncmp(str[(*i)], "EA", 2))
		map->e_path = ft_strdup(str[(*i)] + 2);
}

void	get_diretions(t_map *map, char **str, int *i)
{
	while (!ft_strncmp(str[(*i)], "NO", 2) || !ft_strncmp(str[(*i)], "SO", 2)
		|| !ft_strncmp(str[(*i)], "WE", 2) || !ft_strncmp(str[(*i)], "EA", 2))
	{
		directions(map, str, i);
		(*i)++;
	}
}

void	get_colors(char **str, t_map *map, int *i)
{
	while (!ft_strncmp(str[(*i)], "F", 1) || !ft_strncmp(str[(*i)], "C", 1))
	{
		if (!ft_strncmp(str[(*i)], "F", 1))
			map->f_color = ft_strdup(str[(*i)] + 1);
		else if (!ft_strncmp(str[(*i)], "C", 1))
			map->c_color = ft_strdup(str[(*i)] + 1);
		(*i)++;
	}
}

void	map_fill(char **str, t_map *map)
{
	int	i;

	i = 0;
	get_diretions(map, str, &i);
	get_colors(str, map, &i);
	map->map = &str[i];
	get_map(&str[i], map);
}
