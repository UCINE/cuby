/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojamal <ojamal@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:13:25 by lahamoun          #+#    #+#             */
/*   Updated: 2023/11/29 00:59:15 by ojamal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <ctype.h>
# include <math.h>
# include <stdbool.h>

# define WIN_HIGHT 1000
# define WIN_WIDTH 1000
# define PLAYER_SIZE 10
# define SCREEN_WIDTH 1152
# define SCREEN_HEIGHT 512
# define PLAYER_SPEED 0.1
# define MLX_KEY_W 119
# define MLX_KEY_S 115
# define MLX_KEY_A 97
# define MLX_KEY_D 100
# define KEY_ESC 9
# define SQUARE_SIZE 30
# define MLX_KEY_Q 113
# define MLX_KEY_E 101
# define NORTH 0
# define SOUTH 1
# define WEST 3
# define EAST 2
# define GRID 40

typedef struct s_ray
{
	double	p_y;
	double	p_x;
	double	angle;
	int		hit_horz;
	int		hit_vert;
}			t_ray;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		h;
	int		w;
	double	x;
	double	y;
}			t_image;

typedef struct s_color
{
	int		comma;
	int		flag;
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_map
{
	int		j;
	int		k;
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
	int		pov;
	int		player;
	int		max_line;
	int		map_len;
	int		player_x;
	int		player_y;
	t_color	floor;
	t_color	celling;
}			t_map;

typedef struct s_gameworld
{
	t_map	*map_info;
	t_data	imagetodraw;
	double	dir;
	double	distance;
	int		start;
	int		end;
	int		speed;
	int		mouse_x;
	int		mouse_y;
	int		h;
	int		w;
	void	*win;
	void	*connection;
	double	save_ray_ang;
	double	wall_distance;
	int		current_texture_index;
	double	was_hit_vertical;
	double	was_hit_horizontal;
	double	is_ray_facing_up;
	double	is_ray_facing_down;
	double	is_ray_facing_left;
	double	is_ray_facing_right;
	int		wall_height;
	double	wall_hitx;
	double	wall_hity;
	bool	checkenter;
	t_image	image;
	t_image	t[4];
	int		orientation;
}			t_gameworld;

void		map_fill(char **str, t_map *map);
int			check_rgb(t_color *rgb);
int			msg_er(char *str);
int			check_for_textures(t_map *map);
t_map		*process_map(char *filename);
int			map_check(t_map *map);
void		map_printing(t_map *map);
void		get_map(char **str, t_map *map);
int			check_colors(char *color, t_color *rgb, int i, int j);
void		raycast(t_gameworld *world);
int			ft_moves(int key, t_gameworld *data);
void		draw_elements(t_gameworld *data);
void		my_mlx_pixel_put(t_gameworld *data, int x, int y, int color);
int			check_ups(t_map *map, int i, int j);
int			check_sides(t_map *map, int j, int i);
int			check_for_textures(t_map *map);
void		welcomer(t_gameworld *world);
void		calculate_ray_intersection(t_gameworld *data, t_ray *ray);
void		draw_ray(t_gameworld *data, double ray_y, double ray_x, int j);
void		draw(t_gameworld *data, int j, int color, t_ray ray);
void		realloc_image(t_gameworld *world);
void		draw_wall_s(t_gameworld *data, int j, int color);
void		setup_wall_parameters(t_gameworld *data, t_ray *ray);
void		draw_walls(t_gameworld *data, int j, int color, t_ray *ray);
int			orien(int hit_vert, int hit_horz, double i, t_gameworld *data);
double		ft_distance(double px, double py, double wx, double wy);
void		draw_ceiling_and_floor(t_gameworld *data, int j);
void		get_start_end(t_gameworld *data);
double		wall_hight(t_gameworld *data, double ray);
int			get_texture_color(t_image *texture, int x, int y);
int			check_for_colors(t_map *map);
#endif