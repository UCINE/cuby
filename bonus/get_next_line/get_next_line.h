/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:56:51 by ojamal            #+#    #+#             */
/*   Updated: 2023/11/12 11:52:00 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_mal
{
	int			pos;
	uintptr_t	*ptr;
	int			len;
}				t_mal;

void			*my_malloc(size_t size);
void			my_free(void *address);
void			my_free_all(void);
void			ft_memory_set(void *pointer, int c, size_t len);
void			*ft_memory_copy(void *destination, void *source, size_t len);
char			*get_next_line(int fd);
char			*get_first_line(char *next_line);
char			*get_new_line(char *str);
int				f_strlen(char *s);
char			*f_strjoin(char *s1, char *s2);
char			*f_strchr(char *s, char c);
char			*fd_read(int fd, char *line);

#endif