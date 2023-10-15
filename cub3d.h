#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include "minilibx_opengl_20191021/mlx.h"
# include<stdbool.h>
# include <ctype.h>
# include "./get_next_line/get_next_line.h"

// # define ESC 53
// # define W 13
// # define A 0
// # define S 1
// # define D 2

# define SCREEN_WIDTH 900
# define SCREEN_HEIGHT 800

typedef struct s_map
{
	char	*line;
	char	*get_line;
	char	**map;
	char	**map_clone;
	char	*n_path;
	char	*e_path;
	char	*w_path;
	char	*s_path;
	char	*f_color;
	char	*c_color;
	int		player;
	int		max_line;
	int		map_len;
}	t_map;

typedef struct s_point2D
{
    double	x;
    double	y;
}	t_point2D;

typedef struct s_gridpoint
{
    int	row;
    int	col;
}	t_gridpoint;

typedef struct s_character
{
    t_point2D	location;
    t_point2D	direction;
    t_point2D	viewslice;
}	t_character;

typedef struct s_gameworld
{
    t_character		player;
	void			*mlx;
	void			*window;
	void		 	*mlximage;
    t_map			info;      
    uint32_t		colors[2];
}	t_gameworld;



void	map_fill(char **str, t_map *map);
int		map_check(t_map *map);
void	map_printing(t_map *map);
void	get_map(char **str, t_map *map);
void	free_str(char **str);
int check_west(t_map *map, int i);
int check_east(t_map *map, int i);
int check_north(t_map *map, int i);
int check_south(t_map *map, int i);
int	check_directions(t_map *map);
int check_c_color(t_map *map);
int check_f_color(t_map *map);
#endif