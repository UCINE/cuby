/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 23:43:17 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/12 11:54:52 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rgb(t_color *rgb, int val)
{
	if (rgb->flag == 0)
		rgb->r = val;
	else if (rgb->flag == 1)
		rgb->g = val;
	else if (rgb->flag == 2)
		rgb->b = val;
	rgb->flag++;
}

int	valid_color(char *color, int *i, int *j, t_color *rgb)
{
	int	val;

	val = 0;
	while(ft_isdigit(color[(*i)]))
	{
		val = val * 10 + (color[(*i)++] - '0');
		(*j)++;
	}
	if (val >= 0 && val <= 255 && rgb->flag < 3)
	{
		get_rgb(rgb, val);
		val = 0;
	}
	else
		return msg_er("Invalid color");
	return (0);
}

int check_colors(char *color, t_color *rgb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	rgb->flag = 0;
	while (color[i] == ' ' || color[i] == '\t')
		i++;
	while(color[i])
	{
		if (ft_isdigit(color[i]))
		{
			if (valid_color(color, &i, &j, rgb))
				return (1);
		}
		if (j > 3)
			return msg_er("Invalid color");
		else if (color[i] == ',')
			j = 0;
		else if (color[i] == '\0')
			break;
		i++;
	}
	return (0);
}

