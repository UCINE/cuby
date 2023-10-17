/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 01:23:38 by ojamal            #+#    #+#             */
/*   Updated: 2023/10/17 04:29:26 by lahamoun         ###   ########.fr       */
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

void draw_square(t_gameworld *world, int x_start, int y_start, int size, int color)
{
    int x;
	int y;

    for (y = y_start; y < y_start + size; y++)
    {
        for (x = x_start; x < x_start + size; x++)
        {
			mlx_pixel_put(world->mlx, world->window, x, y, color);
        }
    }
}

void draw_map(t_map *world, t_gameworld *game)
{
    int x;
	int y;

    for (y = 0; world->map[y]; y++)
    {
        for (x = 0; world->map[y][x]; x++)
        {
            if (world->map[y][x] == '1')
            {
                draw_square(game, x * game->tile_size, y * game->tile_size, game->tile_size, 0xFFFFFF);
            }
            else if (world->map[y][x] == '0')
            {
                draw_square(game, x * game->tile_size, y * game->tile_size, game->tile_size, 0x000000);
            }
			else if (world->map[y][x] == 'N')
			{
				draw_square(game, x * game->tile_size, y * game->tile_size, game->tile_size, 0x00FF00);
			}
        }
    }
}

int main(int ac, char **av)
{
	t_gameworld world;

	if (ac != 2)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m ./cub3d <map_path>\n", 2);
		return (1);
	}
	world.map_info = NULL;
	world.tile_size = 0;
	world.map_info = process_map(av[1]);
	if (!world.map_info)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Failed to process map\n", 2);
		return (1);
	}
	world.mlx = mlx_init();
	if (!world.mlx)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Failed to initialize MLX\n", 2);
		return (1);
	}
	world.window = mlx_new_window(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
	if (!world.window)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Failed to create window\n", 2);
		free(world.mlx);
		return (1);
	}
	world.tile_size = calculatetilesize(world.map_info->map);
	printf("Tile Size: %d\n", world.tile_size);
	draw_map(world.map_info, &world);
	world.mlximage = mlx_new_image(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!world.mlximage)
	{
		ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Failed to create image\n", 2);
		mlx_destroy_window(world.mlx, world.window);
		free(world.mlx);
		return (1);
	}

	// mlx_put_image_to_window(world.mlx, world.window, world.mlximage, 0, 0);
	mlx_loop(world.mlx);
	return (0);
}
