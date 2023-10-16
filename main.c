/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 01:23:38 by ojamal            #+#    #+#             */
/*   Updated: 2023/10/15 02:02:39 by ojamal           ###   ########.fr       */
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

int process_map(char *filename)
{
    t_map *map;

    if (check_filename(filename))
        return (1);
	else 
	{
        map = malloc(sizeof(t_map));
        if (!map)  
		{
            ft_putstr_fd("\033[1;31mCube3D:\033[0;0m Memory allocation error\n", 2);
            return (1);
        }
        map = read_map(open(filename, O_RDONLY, 0666), map);
        map_init(map);
        map_fill(map->map, map);
        if (map_check(map)) 
		{
            free_map(&map);
            return (1);
        }
        map_printing(map);
        free_map(&map);
    }
    return (0);
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

void draw_map(t_gameworld *world)
{
    int x;
	int y;
	
    for (y = 0; y < 8; y++)
    {
        for (x = 0; x < 18; x++)
        {
            if (world->map[y][x] == '1')
            {
                draw_square(world, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0xFFFFFF);
            }
            else if (world->map[y][x] == '0')
            {
                draw_square(world, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, 0x000000);
            }
        }
    }
}

int main(int ac, char **av)
{
	t_gameworld world; 

	// if (ac != 2)
	// {
	// 	ft_putstr_fd("\033[1;31mCube3D:\033[0;0m ./cub3d <map_path>\n", 2);
	// 	return (1);
	// }
	(void)ac;
	(void)av;
	//process_map(av[1])
	
	char *static_map[] = {
		"111111111111111111",
		"100000000000000001",
		"100000000000000001",
		"100001000000N00001",
		"100010000000000001",
		"100000000011100001",
		"100000000000000001",
		"111111111111111111",
		NULL
	};
	world.map = static_map;
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

	world.mlximage = mlx_new_image(world.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	draw_map(&world);
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
