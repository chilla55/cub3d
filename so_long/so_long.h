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

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"

/*
** unistd for write
** time for guard and animations
** fcntl for open
*/

# define TILE_SIZE	42

# ifndef USE_ARROW_KEYS
#  define USE_ARROW_KEYS	0
# endif

# ifndef GUARD
#  define GUARD	0
# endif

/*
** 0 for an empty space,
** 1 for a wall,
** C for a Collectible,
** E for a map Exit,
** P for the Player’s starting position
** G for Guard (ERROR for GUARD = 0)
** One *char[] *tiles to hold the whole map as string
** *mlx pointer for the MinilibX components
** **X[] pointers to load all neccessary image files
*/

typedef struct s_map {
	int		height;
	int		width;
	int		p_pos;
	int		g_pos;
	int		p_old;
	int		g_old;
	int		p_key;
	int		g_key;
	int		exitmode;
	int		redraw;
	int		anim_counter;
	int		steps;
	time_t	last_guard_move;
	char	*tiles;
	void	*mlx;
	void	*mlx_win;
	void	**p[4];
	void	**g[4];
	void	**w[4];
	void	**c[4];
	void	**x[7];
	void	**r[5];
	void	**e[1];
	void	**o[16];
}				t_map;

// ft_exit.c
int		ft_exitclick(void *map);
void	ft_exit(t_map *map, int exitmode);

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

// ft_t_map_init.c
t_map	*ft_t_map_init(char *path);

// ft_load_imgs.c
void	ft_load_imgs(t_map *map, int tls);
void	ft_free_imgs(t_map *map);

// ft_t_map_print.c
void	ft_t_map_print(t_map *map);

#endif
