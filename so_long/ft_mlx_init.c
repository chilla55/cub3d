/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:41:39 by skorte            #+#    #+#             */
/*   Updated: 2022/04/06 11:02:50 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** ft_key_hook defines the action that happens upon key-down events.
** The escape key (key code 65307) triggers the program to exit.
** If compiled with arrow key option, arrow keys are redirected
** as "wasd" keys.
** The player is moved and the terminal map redrawn.
*/

static int	ft_key_hook(int key, void *map_void)
{
	t_map	*map;

	map = ((t_map *)map_void);
	if (key == 65307)
		ft_exit (map, 65307);
	if (map->exitmode != 0)
		return (0);
	if (USE_ARROW_KEYS)
	{
		if (key == 65362)
			key = 'w';
		else if (key == 65361)
			key = 'a';
		else if (key == 65364)
			key = 's';
		else if (key == 65363)
			key = 'd';
	}
	if (ft_strchr("wasd", key))
	{
		map->p_key = key;
		ft_move_p(map, key);
		ft_t_map_print(map);
	}
	return (0);
}

/*
** The loop waits 30 ms, so runs with up to 33 fps.
** It only redraws the necessary tiles (player, guard, their old positions).
** If map->redraw is set to 1 (e.g. fresh start or window moved)
** the whole window is redrawn.
** If a guard is present, it is moved once a second.
** The animations to make random stars twinkle and cats wink is run.
** A string with the number of steps is printed in the upper left corner
** of the window.
*/

static int	ft_looping(void *map_void)
{
	t_map	*map;

	map = ((t_map *)map_void);
	if (map->redraw == 1)
		ft_mlx_draw_map(map);
	map->redraw = 0;
	{
		if (ft_input_generator(map))
		{
			ft_move_g(map, map->g_key);
			ft_t_map_print(map);
			ft_redraw_g(map);
		}
		ft_redraw_p(map);
		ft_twinkle_animation(map);
	}
	usleep(30000);
	return (0);
}

/*
** All tiles of the map are drawn into the window.
** This is done on startup and on expose events.
*/

void	ft_mlx_draw_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(map->tiles))
	{
		if (map->tiles[i] == 'P')
			ft_redraw_p(map);
		else if (map->tiles[i] == 'G')
			ft_redraw_g(map);
		else if (map->tiles[i] == '0')
			ft_redraw_0(map, i);
		else if (map->tiles[i] == '1')
			ft_redraw_1(map, i);
		else if (map->tiles[i] == 'C')
			ft_redraw_c(map, i);
		else if (map->tiles[i] == 'E')
			ft_put_image_2(map->e[0], i, map);
		i++;
	}
	if (map->steps)
		ft_draw_step_count(map);
}

/*
** On expose events, the whole map gets redrawn.
*/

int	ft_win_redraw(void *map_void)
{
	t_map	*map;

	map = ((t_map *)map_void);
	map->redraw = 1;
	return (0);
}

/*
** The mlx window, hooks and loops are set up here
*/

void	ft_mlx_init(t_map *map)
{
	int		width;
	int		height;

	width = map->width * TILE_SIZE;
	height = map->height * TILE_SIZE;
	map->mlx = mlx_init();
	if (!map->mlx)
		ft_exit(map, -2);
	map->mlx_win = mlx_new_window
		(map->mlx, width, height, "Save the Caitians!!");
	mlx_do_key_autorepeatoff(map->mlx);
	mlx_expose_hook(map->mlx_win, ft_win_redraw, map);
	mlx_hook(map->mlx_win, 2, (1L << 0), ft_key_hook, map);
	mlx_hook(map->mlx_win, 17, (1L << 17), ft_exitclick, map);
	ft_load_imgs(map, TILE_SIZE);
	mlx_loop_hook(map->mlx, ft_looping, map);
	mlx_loop(map->mlx);
}
