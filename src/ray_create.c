/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 23:30:08 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/05 00:20:13 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void ray_create(t_gameworld *data, double ray_y, double ray_x)
// {
//     double	i = -0.5;
// 	int		j = 1999;
//     while (i <= 0.5)
//     {
// 		int hit_vert = 0, hit_horz = 0;
//         data->distance = 0;
//         double y = ray_y;
//         double x = ray_x;
//         double dy = cos(data->dir + i);
//         double dx = sin(data->dir + i);
//         while (data->map_info->map[(int)y / 40][(int)x / 40] != '1')
//         {
//             //pixel_generator(data, (int)x, (int)y, 0xFFF00F);
// 			if (data->map_info->map[(int)y / 40][(int)(x-dx) / 40] == '1')
// 				hit_vert = 1;
//             if (data->map_info->map[(int)(y-dy) / 40][(int)x / 40] == '1')
// 				hit_horz = 1;
//             x -= dx;
//             y -= dy;
//             data->distance++;
//         }
// 		data->iswallhitx = x;
// 		data->iswallhity = y;
// 		//data->wall_height = wall_hight(data);
// 		//get_start_end(data);
// 		//p = that_wall(data, ray_y, ray_x, data->wall_hity, data->wall_hitx);
// 		// if (hit_horz)
// 		// 	draw(data, j, 0xFFFFF);
// 		// else if (hit_vert)
// 		// 	draw(data, j, 0xFF00FF);
// 		// else
// 		// 	draw(data, j, 0xFF00FF);
// 		j--;
// 		// printf("---------------------------------------\n%f\n", data->distance);
// 		// printf("point of hit: %.1f - %.1f | wall hieght: %f\n", data->wall_hitx, data->wall_hity, data->wall_height);
//         i += 0.001 / 2;
//     }
// 	//printf("[%d]\n", j);
// }