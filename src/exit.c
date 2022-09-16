/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:39:05 by skorte            #+#    #+#             */
/*   Updated: 2022/09/16 14:35:58 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Image sources displayed during regular game exit.
*/

static void	credits(void)
{
	int	fd;

	fd = STDOUT_FILENO;
	write(fd, &"\nGraphics credits:\n", 19);
	write(fd, &" Start screen: Walt Disney's Jungle Book (1967)\n", 48);
}

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
	if (exitmode == 0 || exitmode == 65307)
		credits();
}

/*
** Hitting the "X" in the upper right corner of the window runs a normal exit.
*/

int	exitclick(void *game)
{
	game_exit((t_game *)game, 0);
	return (0);
}

/*
** On exit, all allocated memory is freed and a message displayed.
*/

void	game_exit(t_game *game, int exitmode)
{
	int	i;

	if (game)
	{
		i = 0;
		while (i < 4)
		{
			if (game->image_paths[i])
				free (game->image_paths[i]);
			if (game->mlx_images[i])
				mlx_destroy_image(game->mlx, game->mlx_images[i]);
			i++;
		}
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
		i = 0;
		while (i < X_RES)
		{
			if (game->rays[i] != NULL)
				free (game->rays[i]);
			i++;
		}
		if (game->frame_buffer)
			mlx_destroy_image(game->mlx, game->frame_buffer);
		if (game->mlx_win)
		{
			mlx_destroy_window(game->mlx, game->mlx_win);
		}
		if (game->mlx)
		{
			mlx_destroy_display(game->mlx);
			free(game->mlx);
		}
		free (game);
	}
	exitmessage(exitmode);
	exit (0);
}
