/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raycast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:15:42 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/26 23:32:37 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_gameworld	world;

	if (ac != 2)
		return (msg_er("./cub3d <map_path>"));
	world.map_info = process_map(av[1]);
	if (!world.map_info)
		return (printf("Stopped Here"));
	raycast(&world);
}
