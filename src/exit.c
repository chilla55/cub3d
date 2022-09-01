/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:39:05 by skorte            #+#    #+#             */
/*   Updated: 2022/09/01 23:20:19 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Image sources displayed during regular game exit.
*/

static void	credits(void)
{
	write(1, &"\nGraphics credits:\n", 19);
}

/*
** Exit messages displayed during game exit.
** In case of irregular exit, an Error is printed.
*/

static void	exitmessage(int exitmode)
{
	if (exitmode == 0)
		write (1, "\nNormal exit\n", 13);
	else if (exitmode == -1)
		write (STDERR_FILENO, "\nError:\n Invalid cub file!\n", 27);
	else if (exitmode == -2)
		write (STDERR_FILENO, "\nError:\n MLX failed!\n", 21);
	else if (exitmode == -3)
		write (STDERR_FILENO, "\nError:\n cub file path invalid!\n", 32);
	else if (exitmode < 0)
		write (STDERR_FILENO, "\nError:\n error??\n", 17);
	if (exitmode == 0)
		credits();
}

/*
** A click on the 'x' on the upper right window corner gets redirected
** as press on the escape key.
*/
/*
int	ft_exitclick(void *map)
{
	ft_exit((t_map *)map, 65307);
	return (0);
}
*/
/*
** On exit, all allocated memory is freed and a message displayed.
*/

void	game_exit(t_game *game, int exitmode)
{
	if (game)
	{
		if (game->no_path)
			free (game->no_path);
		if (game->so_path)
			free (game->so_path);
		if (game->we_path)
			free (game->we_path);
		if (game->ea_path)
			free (game->ea_path);
		if (game->f_color)
			free (game->f_color);
		if (game->c_color)
			free (game->c_color);
		while (game->height)
		{
			free (game->map[game->height - 1]);
			game->height--;
		}
		free (game->map);
		free (game);
	}
	exitmessage(exitmode);
	exit (0);
}
/*		ft_t_map_print(map);
	ft_exitmessage(exitmode);
	if (map)
	{
		if (map->tiles)
			free(map->tiles);
		if (map->mlx_win)
		{
			ft_free_imgs(map);
			mlx_destroy_window(map->mlx, map->mlx_win);
		}
		if (map->mlx)
		{
			mlx_destroy_display(map->mlx);
			free(map->mlx);
		}
		free(map);
	}*/
