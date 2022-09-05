/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:59:42 by skorte            #+#    #+#             */
/*   Updated: 2022/09/05 21:10:27 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:52:43 by skorte            #+#    #+#             */
/*   Updated: 2022/04/06 10:52:57 by skorte           ###   ########.fr       */
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

/*
** 0 for an empty space,
** 1 for a wall,
** NSWE for the Player’s starting position and orientation.
** *mlx pointer for the MinilibX components
** **X[] pointers to load all neccessary image files
*/

typedef struct s_ray {
	double	alpha;
	double	x;
	double	y;
	double	d_x;
	double	d_y;
	char	wallface;
	int		h_pixel;
}				t_ray;

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

/*
// ft_move.c
void	ft_move_g(t_map *map, int key);
void	ft_move_p(t_map *map, int key);
int		ft_input_generator(t_map *map);
void	ft_guard_pos_generator(t_map *map);
*/

// mlx_init.c
void	game_mlx_init(t_game *game);

void	load_images(t_game *game);
void	load_start_screen(t_game *game);

//void	ft_mlx_draw_map(t_map *map);
/*
// ft_put_draw.c
void	ft_put_image_2(void *img, int pos, t_map *map);
void	ft_draw_win(t_map *map);
void	ft_draw_caught(t_map *map);
void	ft_draw_step_count(t_map *map);
void	ft_twinkle_animation(t_map *map);

// ft_redraw.c
void	ft_redraw_p(t_map *map);
void	ft_redraw_g(t_map *map);
void	ft_redraw_0(t_map *map, int pos);
void	ft_redraw_1(t_map *map, int pos);
void	ft_redraw_c(t_map *map, int pos);

*/

// game_init.c
t_game	*game_init(char *path);
int		open_cub(char *path);
void	set_player_pos(t_game *game, int x, int y);

// map_test.c
void	map_test(t_game *game);

// load_cub_1.c
void	get_size(t_game *game, int fd);
void	get_no_texture(t_game *game, int fd);
void	get_so_texture(t_game *game, int fd);
void	get_ea_texture(t_game *game, int fd);
void	get_we_texture(t_game *game, int fd);

// load_cub_2.c
void	get_f_color(t_game *game, int fd);
void	get_c_color(t_game *game, int fd);
void	skip_empty_line(t_game *game, int fd);
void	skip_lines(t_game *game, int fd);

// raycasting.c
void	raycaster_init(t_game *game);

#endif
