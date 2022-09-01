/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:59:42 by skorte            #+#    #+#             */
/*   Updated: 2022/09/02 00:00:46 by skorte           ###   ########.fr       */
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
# include <stdio.h> //remove??
# include "../lib/libft/libft.h"
# include "../lib/minilibx-linux/mlx.h"

/*
** unistd for write
** stdlib for malloc and free
** time for loop timing??
** fcntl for open
*/

# define X_RES = 640
# define Y_RES = 480

# ifndef USE_ARROW_KEYS
#  define USE_ARROW_KEYS	0
# endif

/*
** 0 for an empty space,
** 1 for a wall,
** NSWE for the Player’s starting position and orientation
** One *char[] *tiles to hold the whole map as string
** *mlx pointer for the MinilibX components
** **X[] pointers to load all neccessary image files
*/

typedef struct s_game {
	int		height;
	int		width;
	double	x_pos;
	double	y_pos;
	double	angle;
	char	**map;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_color;
	char	*c_color;
	void	*mlx;
	void	*mlx_win;
}				t_game;

// exit.c
int		ft_exitclick(void *map);
void	game_exit(t_game *game, int exitmode);
/*
// ft_move.c
void	ft_move_g(t_map *map, int key);
void	ft_move_p(t_map *map, int key);
int		ft_input_generator(t_map *map);
void	ft_guard_pos_generator(t_map *map);

// ft_mlx_init.c
void	ft_mlx_init(t_map *map);
void	ft_mlx_draw_map(t_map *map);

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
// ft_t_map_init.c
t_game	*game_init(char *path);

/*
// ft_load_imgs.c
void	ft_load_imgs(t_map *map, int tls);
void	ft_free_imgs(t_map *map);

// ft_t_map_print.c
void	ft_t_map_print(t_map *map);
*/

void	raycaster_init(t_game *game);

#endif
