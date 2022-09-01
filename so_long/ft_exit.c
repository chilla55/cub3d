/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:39:05 by skorte            #+#    #+#             */
/*   Updated: 2022/04/07 18:36:52 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Image sources displayed during regular game exit.
*/

static void	ft_credits(void)
{
	int	i;

	i = write(1, &"\nGraphics credits:\n", 19);
	i = write(1, &"ships: deviantart.com/vampireslug\n", 34);
	i = write(1, &"stars: vectorpixelstar.itch.io\n", 31);
	i = write(1, &"earth: shutterstock.com/image-vector/188621246\n", 47);
	i = write(1, &"rocks: adapted from wallpaperflare.com\n", 40);
	i += write(1, &"cats: pixelrogueart.newgrounds.com\n\n", 36);
}

/*
** Exit messages displayed during game exit.
** In case of irregular exit, an Error is printed.
*/

static void	ft_exitmessage(int exitmode)
{
	int	i;

	i = 0;
	if (exitmode == 1)
		i = write (1, "\nYeah, you made it!\nAll Caitians are saved!\n", 44);
	else if (exitmode == 2)
		i = write (1, "\nUh, you got destroyed by a Klingon warship!\n", 45);
	else if (exitmode == 65307)
		i = write (1, "\nEscaping...\n", 13);
	else if (exitmode == -1)
		i = write (STDERR_FILENO, "\nError:\n Invalid map!\n", 22);
	else if (exitmode == -2)
		i = write (STDERR_FILENO, "\nError:\n MLX failed!\n", 21);
	else if (exitmode == -3)
		i = write (STDERR_FILENO, "\nError:\n Map path invalid!\n", 28);
	else if (exitmode < 0)
		i += write (STDERR_FILENO, "\nError:\n error??\n", 17);
	if (exitmode > 0)
		ft_credits();
}

/*
** A click on the 'x' on the upper right window corner gets redirected
** as press on the escape key.
*/

int	ft_exitclick(void *map)
{
	ft_exit((t_map *)map, 65307);
	return (0);
}

/*
** On exit, all allocated memory is freed and a message displayed.
*/

void	ft_exit(t_map *map, int exitmode)
{
	if (exitmode > 0)
		ft_t_map_print(map);
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
	}
	exit (0);
}
