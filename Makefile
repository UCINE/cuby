# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/27 01:17:39 by lahamoun          #+#    #+#              #
#    Updated: 2023/11/28 22:41:17 by ojamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          = cc

NAME        = cub3D

B_NAME        = cub3D_bonus

LIBFT_NAME  = libft.a

SRCS        = src/check_colors.c src/get_map.c src/main_raycast.c src/map_check.c \
				 get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_next_line/leaks_free_utils.c get_next_line/leaks_free.c \
				 src/map_size.c src/parse.c src/raycasting.c src/twod.c src/utils.c src/map_check2.c src/raycast_norm.c src/ft_norm.c src/raycasting2.c \
				 

B_SRCS        = bonus/src/check_colors.c bonus/src/get_map.c bonus/src/main_raycast.c bonus/src/map_check.c \
				 get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_next_line/leaks_free_utils.c get_next_line/leaks_free.c \
				 bonus/src/map_size.c bonus/src/parse.c bonus/src/raycasting.c bonus/src/twod.c bonus/src/utils.c bonus/src/map_check2.c \
				 bonus/src/raycast_norm.c bonus/src/ft_norm.c bonus/src/raycasting2.c

OBJ         = $(SRCS:.c=.o)

B_OBJ         = $(B_SRCS:.c=.o)

CFLAGS      = -Wall -Wextra -Werror

LINUX_FLAGS = -L libft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

bonus: $(B_NAME)

%.o:%.c
	@$(CC) $(CFLAGS) $(LINUX_FLAGS) -O3 -c $< -o $@
	@echo "\033[1;32mCompiling... " $@ "\033[0;0m"

$(NAME): $(OBJ)
	@make -s -C libft
	@$(CC) $(OBJ) $(CFLAGS) $(LINUX_FLAGS) -o $(NAME)
	@echo "\033[1;32mDone Compiling !\033[0;0m"

$(B_NAME): $(B_OBJ)
	@make -s -C libft
	@$(CC) $(B_OBJ) $(CFLAGS) $(LINUX_FLAGS) -o $(B_NAME)
	@echo "\033[1;32mDone Compiling Bonus!\033[0;0m"

clean:
	@make -s -C libft clean
	@rm -rf $(OBJ)
	@rm -rf $(B_OBJ)
	@echo "\033[1;31mDone Cleaning!\033[0;0m"

fclean: clean
	@make -s -C libft fclean
	@rm -rf $(NAME)
	@rm -rf $(B_NAME)
	@echo "\033[1;31mDone Full Cleaning!\033[0;0m"

re: fclean all