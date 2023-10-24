/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_directions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 00:00:21 by ojamal            #+#    #+#             */
/*   Updated: 2023/10/24 11:52:52 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_path(char *str)
{
	int	i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
		i++;
	while(str[i])
	{
		if (str[i] == '.' && ft_isalpha(str[i + 1]))
		{
			if (!ft_strcmp(&str[i], ".xpm"))
				return (0);
			else
			{
				ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid texture path\n",
					2);
				return (1);
			}
		}
		else if (str[i] == ' ' || str[i] == '\t')
			return (ft_putstr_fd("\033[1;31mCube3D :\033[0;0m Invalid texture path\n",
				2), 1);
		i++;
	}
    return (0);
}
