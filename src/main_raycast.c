/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:15:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/14 04:10:41 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// int xt = game->map_info->player_x, yt = game->map_info->player_y;
	// for (int i = 0; i < 15;i++)
	// {
	// 	mlx_pixel_put(game->mlx, game->window, xt, yt, 0xf00);
	// 	xt += cos(game->player.direction);
	// 	yt -= sin(game->player.direction);
	// }

/*instead of using function definition in the headerfile 
	try to use this

double	deg_to_rad(double degrees){
	return (degrees * M_PI / 180);
}*/


int main(int ac, char **av)
{
	t_gameworld world;

	if (ac != 2)
		return msg_er("./cub3d <map_path>");
	world.map_info = process_map(av[1]);
	printf("yooooo");
	if (!world.map_info)
        return (printf("Stopped Here"));
	// map_printing(world.map_info);
    printf("%d\n", world.map_info->pov);
    raycast(&world);
}