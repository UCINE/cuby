/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:12:11 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/28 21:56:03 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	if (size != 0 && count >= SIZE_MAX / size)
		return (NULL);
	str = my_malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, (count * size));
	return (str);
}
// int main()
// {
// 	//char	str[] = "Hello ";
// 	char *ptr;
// 	ptr = (char *)my_malloc(6 * sizeof(char));
// 	for (int x = 0;x <= 6;x++)
// 		printf("ptr[%d] --> %d\n", x, ptr[x]);
// }