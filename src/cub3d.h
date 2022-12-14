/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:59:42 by skorte            #+#    #+#             */
/*   Updated: 2022/10/29 22:42:31 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"

/*
** unistd for write
** stdlib for malloc and free
** time for loop timing??
** fcntl for open
*/

# define X_RES 1280
# define Y_RES 720
# define PI (double)3.1415926

# define POS_SIGN 1
# define NEG_SIGN 0

# define SUB_STEPS 1
# define MOV_STEP 0.1
# define ANGLE_STEP 5.0

# ifdef __APPLE__
#  define KEY_CODE_W 13
#  define KEY_CODE_A 0
#  define KEY_CODE_S 1
#  define KEY_CODE_D 2
#  define KEY_CODE_ESC 53
#  define KEY_CODE_LEFT 123
#  define KEY_CODE_RIGHT 124
# else
#  define KEY_CODE_W 119
#  define KEY_CODE_A 97
#  define KEY_CODE_S 115
#  define KEY_CODE_D 100
#  define KEY_CODE_ESC 65307
#  define KEY_CODE_LEFT 65361
#  define KEY_CODE_RIGHT 65363
# endif

/*
** t_ray struct, contains the data for one ray.
** It will be used to draw one vertical pixel line.
**
** alpha_0 =  angle from the main direction. Calculated once at game start.
** alpha = angle of the ray in the map, the sum of game->angle and alpha_0.
** height = apparent wall height, calculated from distance and direction.
** wallface = N, E, S or W, defining the texture of the wall.
** h_pixel = between 0 and 1, defining the place where the ray hits the wall.
*/

typedef struct s_ray {
	double	alpha_0;
	double	alpha;
	double	x;
	double	y;
	int		d_x_sign;
	int		d_y_sign;
	double	d_x;
	double	d_y;
	double	distance;
	int		height;
	char	wallface;
	double	h_pixel;
}				t_ray;

typedef struct s_buff {
	char	*buffer;
	int		pixel_bits;
	int		line_bytes;
	int		x_size;
	int		y_size;
	int		endian;
}				t_buff;

typedef struct s_color
{
	char	b;
	char	g;
	char	r;
	char	a;
}	t_color;

/*
** **map:
** 	0 for an empty space,
** 	1 for a wall,
** 	NSWE for the Player???s starting position and orientation.
**
** x_pos, y_pos, angle for the current camera position/orientation.
**
** Pointers to all ray structs.
**
** *mlx pointer for the MinilibX components
** **X[] pointers to load all neccessary image files
*/

typedef struct s_game {
	char	**map;
	int		height;
	int		width;
	int		error;
	double	scale;
	double	x_pos;
	double	y_pos;
	double	angle;
	t_ray	*rays[X_RES];

	t_color	f_color;
	t_color	c_color;
	void	*mlx;
	void	*mlx_win;
	char	*image_paths[4];
	void	*mlx_images[4];
	t_buff	*textures[4];
	void	*frame_buffer;
	t_buff	*buffer;
}				t_game;

// exit.c
int		exitclick(void *game);
void	game_exit(t_game *game, int exitmode);

// exit_mac.c & exit_linux.c
void	free_buffers(t_game *game);

// mlx_init.c
void	game_mlx_init(t_game *game);

void	load_images(t_game *game);
void	load_start_screen(t_game *game);

// game_init.c
t_game	*game_init(char *path);
int		open_cub(t_game *game, char *path);
void	set_player_pos(t_game *game, int x, int y);

// map_test.c
void	map_test(t_game *game);

// load_cub_1.c
void	get_size(t_game *game, int fd, char *line);

// load_cub_2.c
void	skip_empty_line(t_game *game, int fd);
void	skip_lines(t_game *game, int fd, int lts);

// map/get_texture.c
int		parse_texture(t_game *game, char **line);

// map/parse.c
void	parse_option(int fd, t_game *game, int *i, char **line);
void	check_options(t_game *game);
void	parse_map(int fd, t_game *game, int i);

// map/encode_rgb.c
t_color	getcolor(int a, int r, int g, int b);
t_color	encode_rgb(char *str, t_game *game);

// utils/free_split.c
void	free_split(char **split);

// raycasting_init.c
void	raycaster_init(t_game *game);

// raycasting.c
void	raycasting(t_game *game);

// raycasting_find_wall.c
void	ray_find_wall(t_game *game, int ray);

// angle_helpers.c
double	cal_degree(double radian);
double	cal_radian(double degree);

// keyhooks.c
int		key_hook(int key, void *game_void);

int		game_loop(t_game *game);
void	fill_buffer(t_game *game);

// mlx_lixel_handler.c
t_color	extract_pixel(t_buff *buffer, int x, int y);
void	draw_pixel(t_buff *buffer, t_color color, int x, int y);

#endif
