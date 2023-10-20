# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/17 10:29:42 by lahamoun          #+#    #+#              #
#    Updated: 2023/10/20 22:26:54 by ojamal           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

NAME = cub3D
LIBFT = libft.a
LIBFT_DIR = ./libft

INCLUDES = -I/usr/include -Imlx -I$(LIBFT_DIR)
SRC_DIR = ./src/
SRC_DIR2 = ./get_next_line/
OBJ_DIR = ./obj/

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LINK_FLAGS = -L $(LIBFT_DIR) -lft -L../minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME_S),Darwin)
    LINK_FLAGS = -L $(LIBFT_DIR) -lft -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

SRCS = $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR2)*.c)
OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(patsubst $(SRC_DIR2)%.c,$(OBJ_DIR)%.o,$(SRCS)))
DEPS = $(OBJS:.o=.d)

all: $(NAME)

-include $(DEPS)

relink:
	@if [ -f $(NAME) ] && [ $(NAME) -nt $(word 1,$(OBJS)) ]; then \
		echo "HUH?, change something first!"; \
		false; \
	fi

$(NAME): relink $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINK_FLAGS) -o $(NAME)
	@echo "$(GREEN)Done!$(NC)"
	@echo "$(GREEN)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR2)%.c
	@mkdir -p $(@D)
	@echo "$(GREEN)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

$(OBJS): | $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(RED)Cleaning up...$(NC)"
	@sleep 0.5
	@rm -f $(OBJS) $(DEPS)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@sleep 0.5
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all



