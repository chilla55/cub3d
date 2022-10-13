/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:05:50 by skorte            #+#    #+#             */
/*   Updated: 2022/10/13 16:19:50 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Buffers an mlx_image, so it can be modified.
*/

static void	buffer_texture(t_game *game, int i, int x_size, int y_size)
{
	game->textures[i]->buffer = mlx_get_data_addr(game->mlx_images[i],
			&game->textures[i]->pixel_bits,
			&game->textures[i]->line_bytes,
			&game->textures[i]->endian);
	game->textures[i]->x_size = x_size;
	game->textures[i]->y_size = y_size;
}

/*
** Loads the *.xpm textures into mlx-images linked in the game struct.
*/

void	load_images(t_game *game)
{
	int	i;
	int	x_size;
	int	y_size;

	x_size = 0;
	y_size = 0;
	i = 0;
	while (i < 4)
	{
		game->mlx_images[i] = mlx_xpm_file_to_image
			(game->mlx, game->image_paths[i], &x_size, &y_size);
		printf("%s\n", game->image_paths[i]);
		if (!game->mlx_images[i])
			game_exit(game, -4);
		game->textures[i] = malloc(sizeof(t_buff));
		if (!game->textures[i])
			game_exit(game, -4);
		buffer_texture(game, i, x_size, y_size);
		i++;
	}
	return ;
}

void	load_start_screen(t_game *game)
{
	int	x_res;
	int	y_res;

	x_res = 0;
	y_res = 0;
	game->frame_buffer = mlx_xpm_file_to_image
		(game->mlx, "./img/cubs.xpm", &x_res, &y_res);
}
