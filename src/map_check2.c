/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:27:04 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/26 23:37:42 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_for_textures(t_map *map)
{
	if (!map->n_path)
		return (msg_er("Invalid texture"));
	if (!map->e_path)
		return (msg_er("Invalid texture"));
	if (!map->s_path)
		return (msg_er("Invalid texture"));
	if (!map->w_path)
		return (msg_er("Invalid texture"));
	return (0);
}

int	check_ups(t_map *map, int i, int j)
{
	int	k;

	k = i - 1;
	if (k > 0 && map->map_clone[k][j] != '1' && map->map_clone[k][j] != 'x')
		return (msg_er("Unclosed Wall"));
	k = i + 1;
	if (k < map->map_len && map->map_clone[k][j] != '1'
		&& map->map_clone[k][j] != 'x' && map->map_clone[k][j] != '0')
		return (msg_er("Unclosed Wall"));
	return (0);
}

int	check_sides(t_map *map, int j, int i)
{
	int	k;

	k = j - 1;
	if (k > 0 && map->map_clone[i][k] != '1' && map->map_clone[i][k] != 'x')
		return (msg_er("Unclosed Wall"));
	k = j + 1;
	if (k > 0 && k < map->max_line && map->map_clone[i][k] != '1'
		&& map->map_clone[i][k] != 'x' && map->map_clone[i][k] != '0')
		return (msg_er("Unclosed Wall"));
	return (0);
}
