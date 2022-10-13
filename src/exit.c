/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:39:05 by skorte            #+#    #+#             */
/*   Updated: 2022/10/13 16:48:35 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Image sources displayed during regular game exit.
*/

static void	free_map(t_game *game);

/*
** Exit messages displayed during game exit.
** In case of irregular exit, an Error is printed.
*/

static void	exitmessage(int exitmode)
{
	if (exitmode == 0)
		write (STDOUT_FILENO, "\nNormal exit\n", 13);
	else if (exitmode == 65307)
		write (STDOUT_FILENO, "\nESC pressed. Normal exit\n", 26);
	else if (exitmode == -1)
		write (STDERR_FILENO, "\nError:\n Invalid cub file!\n", 27);
	else if (exitmode == -2)
		write (STDERR_FILENO, "\nError:\n MLX failed!\n", 21);
	else if (exitmode == -3)
		write (STDERR_FILENO, "\nError:\n cub file path invalid!\n", 32);
	else if (exitmode == -4)
		write (STDERR_FILENO, "\nError:\n Wall texture not found!\n", 33);
	else if (exitmode < 0)
		write (STDERR_FILENO, "\nError:\n error??\n", 17);
}

/*
** On exit, all allocated memory is freed and a message displayed.
*/

void	game_exit(t_game *game, int exitmode)
{
	int	i;

	if (game)
	{
		free_buffers(game);
		free_map(game);
		i = 0;
		while (i < X_RES)
		{
			if (game->rays[i] != NULL)
				free (game->rays[i]);
			i++;
		}
		free (game);
	}
	exitmessage(exitmode);
	exit (0);
}

static void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (i < game->height)
		{
			if (game->map[i])
				free (game->map[i]);
			i++;
		}
		free (game->map);
	}
}
