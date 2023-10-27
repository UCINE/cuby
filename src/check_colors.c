/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:43:17 by ojamal            #+#    #+#             */
/*   Updated: 2023/10/26 23:23:57 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_color(char *color, int *i, int *j)
{
	int val;

	val = 0;
	while(ft_isdigit(color[(*i)]))
	{
		val = val * 10 + (color[(*i)++] - '0');
		(*j)++;
	}
	if (val >= 0 && val <= 255)
		val = 0;
	else
		return (ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid celling color\n", 2)
			, 1);
	return (0);
}

int check_colors(char *color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	while(color[i])
	{
		if (ft_isdigit(color[i]))
			valid_color(color, &i, &j);
		if (j > 3)
			return (ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid celling color\n", 2), 1);
		else if (color[i] == ',')
			j = 0;
		i++;
	}
	return (0);
}

