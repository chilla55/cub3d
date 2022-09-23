/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 21:46:07 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 10:12:00 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	raycaster_cal_default_angles(t_game *game);

/*
	X_RES rays, spaced between angle-45 to angle+45 - not equally...
	Each needs distance to wall, type of wall face (NSWE),
	and point on wall (between 0 and 1 to extract from texture)
*/

void	raycaster_init(t_game *game)
{
	int		i;

	i = 0;
	while (i < X_RES)
	{
		game->rays[i] = malloc(sizeof(t_ray));
		if (game->rays[i] == NULL)
			game_exit(game, -42);
		i++;
	}
	raycaster_cal_default_angles(game);
	raycasting(game);
}

static void	raycaster_cal_default_angles(t_game *game)
{
	int		i;

	i = 0;
	while (i < X_RES)
	{
		game->rays[i]->alpha_0 = atan(((double)i + 0.5 - (double)X_RES / 2.0)
				/ ((double)X_RES / 2.0));
		i++;
	}
}
