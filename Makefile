CC          = cc

NAME        = cub3D

LIBFT_NAME  = libft.a

SRCS        =   get_next_line/get_next_line.c get_next_line/get_next_line_utils.c main.c parse.c\
				utils.c map_check.c check_directions.c check_colors.c

OBJ         = $(SRCS:.c=.o)

CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address

IMAC_FLAGS	= -L libft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

#LINUX_FLAGS = -L libft -lft -lmlx -L/usr/lib -I/usr/local/include -lXext -lX11 -lm -lz

LINUX_FLAGS	= -L libft -lft -L../minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LINK_FLAGS=$(LINUX_FLAGS)
endif
ifeq ($(UNAME_S),Darwin)
    LINK_FLAGS=$(IMAC_FLAGS)
endif

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LINK_FLAGS) -o $(NAME)

clean:
	@make -C libft clean
	@rm -rf $(OBJ)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: fclean all
