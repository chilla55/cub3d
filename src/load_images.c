/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:05:50 by skorte            #+#    #+#             */
/*   Updated: 2022/09/17 14:43:03 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	buffer_texture(t_game *game, int i);

/*
** Buffers an mlx_image, so it can be modified.
*/

static void	buffer_texture(t_game *game, int i)
{
	game->textures[i]->buffer = mlx_get_data_addr(game->mlx_images[i],
			&game->textures[i]->pixel_bits,
			&game->textures[i]->line_bytes,
			&game->textures[i]->endian);
}

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
		game->textures[i] = malloc(sizeof(t_buff));
		if (!game->textures[i])
			game_exit(game, -4);
		buffer_texture(game, i);
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
