/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:05:50 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 19:20:51 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Loads the *.xpm textures into mlx-images linked in the game struct.
*/

void	load_images(t_game *game)
{
	int	i;
	int	tls;

	tls = TILE_SIZE;
	i = 0;
	while (i < 4)
	{
		game->mlx_images[i] = mlx_xpm_file_to_image
			(game->mlx, game->image_paths[i], &tls, &tls);
		if (!game->mlx_images[i])
			game_exit(game, -4);
		i++;
	}
	return ;
}

void	load_start_screen(t_game *game)
{
	int	x_res;
	int	y_res;

	x_res = X_RES;
	y_res = Y_RES;
	game->frame_buffer = mlx_xpm_file_to_image
		(game->mlx, "./img/cubs.xpm", &x_res, &y_res);
}
