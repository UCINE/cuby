CC          = cc

NAME        = cub3D

LIBFT_NAME  = libft.a

SRCS        = src/check_colors.c src/get_map.c src/main_raycast.c src/map_check.c \
				 get_next_line/get_next_line.c get_next_line/get_next_line_utils.c get_next_line/leaks_free_utils.c get_next_line/leaks_free.c \
				 src/map_size.c src/parse.c src/raycasting.c src/twod.c src/utils.c

OBJ         = $(SRCS:.c=.o)

CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address

LINUX_FLAGS = -L libft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)


%.o:%.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
	@echo "\033[1;32mCompiling... " $@ "\033[0;0m"

$(NAME): $(OBJ)
	@make -C libft
	@$(CC) $(OBJ) $(CFLAGS) $(LINUX_FLAGS) -o $(NAME)
	@echo "\033[1;32mDone Compiling !\033[0;0m"

clean:
	@rm -rf $(OBJ)
	@make -s -C libft clean
	@echo "\033[1;31mDone Cleaning!\033[0;0m"

fclean: clean
	@rm -rf $(NAME)
	@make -s -C libft fclean
	@echo "\033[1;31mDone Full Cleaning!\033[0;0m"

re: fclean all