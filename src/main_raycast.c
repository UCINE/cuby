/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:15:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/04 22:02:18 by lahamoun         ###   ########.fr       */
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
			{
				ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid map name\n",
					2);
				return (1);
			}
		}
		else if (!str[i + 1])
			return (ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid map name\n",
				2), 1);
		i++;
	}
	return (0);
}

t_map	*read_map(int fd, t_map *map)
{
	if (fd == -1)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Invalid file", 2);
		return (NULL);
	}
	map->get_line = NULL;
	map->line = NULL;
	map->get_line = get_next_line(fd);
	if (!map->get_line)
	{
		ft_putendl_fd("\033[1;31mCube3D:\033[0;0m Invalid file", 2);
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

void	free_map(t_map **map)
{
	free((*map)->n_path);
	free((*map)->e_path);
	free((*map)->w_path);
	free((*map)->s_path);
	free((*map)->f_color);
	free((*map)->c_color);
	free_str((*map)->map_clone);
	free(*map);
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

t_map *process_map(char *filename)
{
    t_map *map;

    if (check_filename(filename))
        return (NULL);
	else
	{
        map = malloc(sizeof(t_map));
        if (!map)  
		{
            ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Memory allocation error\n", 2);
            return (NULL);
        }
        map = read_map(open(filename, O_RDONLY, 0666), map);
        map_init(map);
        map_fill(map->map, map);
		if (map_check(map))
			return NULL;
	}
    return (map);
}
	// int xt = game->map_info->player_x, yt = game->map_info->player_y;
	// for (int i = 0; i < 15;i++)
	// {
	// 	mlx_pixel_put(game->mlx, game->window, xt, yt, 0xf00);
	// 	xt += cos(game->player.direction);
	// 	yt -= sin(game->player.direction);
	// }

int main(int ac, char **av)
{
	t_gameworld world;

	if (ac != 2)
		return (ft_putstr_fd("\033[1;31mCube3D:\033[0;0m ./cub3d <map_path>\n", 2), 1);
	world.map_info = process_map(av[1]);
	if (!world.map_info)
        return (printf("Stopped Here"));
    printf("%c\n", world.map_info->pov);
    raycast(&world);
}