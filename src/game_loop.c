/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:41:16 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 20:06:13 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_game *game)
{
	int	i;
	
	i = 0;
	while (i < X_RES)
	{
		game->rays[i]->distance = raycast_ray_init(game, i);
		game->rays[i]->height = (int)(Y_RES / 2 / game->rays[i]->distance);
		i++;
	}
	fill_buffer(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	return (0);
}
