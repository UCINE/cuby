/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 16:36:16 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/28 21:20:10 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_filename(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (!ft_strcmp(&str[i], ".cub"))
				return (0);
			else
				return (msg_er("Invalid map name"));
		}
		else if (!str[i + 1])
			return (msg_er("Invalid map name"));
		i++;
	}
	return (0);
}

t_map	*read_map(int fd, t_map *map)
{
	if (fd == -1)
	{
		msg_er("Invalid file");
		return (NULL);
	}
	map->get_line = NULL;
	map->line = NULL;
	map->get_line = get_next_line(fd);
	if (!map->get_line)
	{
		msg_er("Invalid file");
		return (NULL);
	}
	while (map->get_line)
	{
		map->line = ft_strjoin(map->line, map->get_line);
		free(map->get_line);
		map->get_line = get_next_line(fd);
	}
	free(map->get_line);
	map->map = ft_split(map->line, '\n');
	free(map->line);
	return (map);
}

void	map_init(t_map *map)
{
	map->c_color = NULL;
	map->f_color = NULL;
	map->e_path = NULL;
	map->w_path = NULL;
	map->s_path = NULL;
	map->n_path = NULL;
	map->player = 0;
	map->player_x = 0;
	map->player_y = 0;
}

t_map	*process_map(char *filename)
{
	t_map	*map;

	if (check_filename(filename))
		return (NULL);
	else
	{
		map = my_malloc(sizeof(t_map));
		if (!map)
		{
			msg_er("Memory allocation failed");
			return (NULL);
		}
		map = read_map(open(filename, O_RDONLY, 0666), map);
		map_init(map);
		map_fill(map->map, map);
		if (map_check(map))
			return (NULL);
	}
	return (map);
}
