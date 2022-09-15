/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:59:42 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 15:01:11 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h> //remove??
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"

/*
** unistd for write
** stdlib for malloc and free
** time for loop timing??
** fcntl for open
*/

# define X_RES 1280
# define Y_RES 720
# define PI (double)3.1415926

# define TILE_SIZE	42
# define POS_SIGN 1;
# define NEG_SIGN 0;



typedef struct s_ray {
	double	alpha_0; // angle from the main direction. Calculated once at game start.
	double	alpha;  // angle of the ray in the map, the sum of game->angle and alpha_0.
	double	x;
	double	y;
	int		d_x_sign;
	int		d_y_sign;
	double	d_x;
	double	d_y;
	double	distance;
	int 	height; // apparent wall height, calculated from distance and direction.
	char	wallface; // N, E, S or W, defining the texture of the wall.
	double	h_pixel;  // between 0 and 1, defining the place where the ray hits the wall.
}				t_ray;

/*
** **map:
** 	0 for an empty space,
** 	1 for a wall,
** 	NSWE for the Player’s starting position and orientation.
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
	double	x_pos;
	double	y_pos;
	double	angle;
	t_ray	*rays[X_RES];

	char	*f_color;
	char	*c_color;
	void	*mlx;
	void	*mlx_win;
	char	*image_paths[4];
	void	*mlx_images[4];
	void	*frame_buffer;
}				t_game;

// exit.c
int		exitclick(void *game);
void	game_exit(t_game *game, int exitmode);

// mlx_init.c
void	game_mlx_init(t_game *game);

void	load_images(t_game *game);
void	load_start_screen(t_game *game);

// game_init.c
t_game	*game_init(char *path);
int	open_cub(t_game *game, char *path);
void	set_player_pos(t_game *game, int x, int y);

// map_test.c
void	map_test(t_game *game);

// load_cub_1.c
void	get_size(t_game *game, int fd);

// load_cub_2.c
void	skip_empty_line(t_game *game, int fd);
void	skip_lines(t_game *game, int fd, int lts);

// map/parse.c
void	parse_option(int fd, t_game *game, int *i);
void	parse_map(int fd, t_game *game, int i);

// raycasting.c
void	raycaster_init(t_game *game);
double	raycast_ray_init(t_game *game, int ray);

// angle_helpers.c
double	cal_degree(double radian);
double	cal_radian(double degree);

// keyhooks.c
int		key_hook(int key, void *game_void);


int		game_loop(t_game *game);
void	fill_buffer(t_game *game);

#endif
