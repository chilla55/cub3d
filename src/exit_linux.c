/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_linux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:32:33 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/10/12 18:14:47 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_buffers(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i])
			free (game->textures[i]);
		if (game->image_paths[i])
			free (game->image_paths[i]);
		if (game->mlx_images[i])
			mlx_destroy_image(game->mlx, game->mlx_images[i]);
		i++;
	}
	if (game->buffer)
		free (game->buffer);
	if (game->frame_buffer)
		mlx_destroy_image(game->mlx, game->frame_buffer);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
