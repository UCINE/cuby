/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leaks_free_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 11:50:48 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/12 11:52:34 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_mal	*head(void)
{
	static t_mal	curr;

	if (curr.ptr == NULL)
	{
		curr.len = 10;
		curr.ptr = malloc(curr.len * sizeof(uintptr_t));
	}
	return (&curr);
}

int	get_available_pos(void)
{
	t_mal	*curr;
	int		pos;

	pos = 0;
	curr = head();
	while (pos < curr->pos)
	{
		if (curr->ptr[pos] == 0)
			break ;
		pos++;
	}
	return (pos);
}

void	*my_malloc(size_t size)
{
	t_mal		*curr;
	void		*new;
	uintptr_t	*ptr;
	int			pos;

	new = malloc(size);
	ft_memory_set(new, 0, size);
	pos = get_available_pos();
	curr = head();
	curr->ptr[pos] = (uintptr_t) new;
	if (pos == curr->pos)
		curr->pos++;
	if (curr->pos + 2 >= curr->len)
	{
		ptr = malloc(curr->len * 2 * sizeof(uintptr_t));
		ft_memory_copy(ptr, curr->ptr, curr->len * sizeof(uintptr_t));
		free(curr->ptr);
		curr->ptr = ptr;
		curr->len *= 2;
	}
	return (new);
}

void	my_free(void *address)
{
	t_mal	*curr;
	int		i;

	curr = head();
	i = 0;
	while (i < curr->pos && curr->ptr[i] != (uintptr_t)address)
		i++;
	if (curr->ptr[i] == (uintptr_t)address)
	{
		free((void *)curr->ptr[i]);
		curr->ptr[i] = 0;
	}
}

void	my_free_all(void)
{
	t_mal	*curr;
	int		i;

	curr = head();
	i = 0;
	while (i < curr->pos)
	{
		free((void *)curr->ptr[i]);
		curr->ptr[i] = 0;
		i++;
	}
}
