/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/05 19:39:03 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	X_RES rays, equally??? spaced between angle-45 to angle+45 - No, not equally...
	each needs distance to wall, type of wall face (NSWE),
	and point on wall (between 0 and 1 to extract from texture)
*/

void	raycaster_init(t_game *game)
{
	int		i;

	i = 0;
	printf("\nCalculating default ray directions\n");
	while (i < X_RES)
	{
		game->rays[i] = malloc(sizeof(t_ray));
		game->rays[i]->alpha = atan(((double)i + 0.5 - (double)X_RES / 2.0)
				/ ((double)X_RES / 2.0));
		printf("%f\n", game->rays[i]->alpha * 360 / 2 / PI);
		i++;
	}
}

int	check_x_wall(t_game *game, double x, double d_x, double alpha)
{
	double	y;

	y = game->y_pos + d_x / cos (alpha);
	(void)x;
	(void)y;
	return (0);
}

double	raycast_find_wall(t_game *game, double x, double y, double angle)
{
	double	d_x;
	double	d_y;

	d_x = (x - game->x_pos) / sin(game->angle);
	d_y = (y - game->y_pos) / cos(game->angle);
	if (d_x < d_y)
	{
		if (check_x_wall(game, x, d_x, angle))
			return (d_x);
		if (x > game->x_pos)
			x = x + 1.0;
		else
			x = x - 1.0;
	}
	else
	{
		//if (check_y_wall(game, d_y, alpha))
		//	return (d_y);
		if (y > game->y_pos)
			y = y + 1.0;
		else
			y = y - 1.0;
	}
	return (raycast_find_wall(game, x, y, angle));
}

double	raycast_ray_init(t_game *game, int ray)
{
	double	x;
	double	y;
	double	angle;

	angle = atan(((double)ray + 0.5 - (double)X_RES / 2.0)
			/ ((double)X_RES / 2.0)) + game->angle * PI / 180;
	x = ceil(game->x_pos);
	y = ceil(game->y_pos);
	return (raycast_find_wall(game, x, y, angle));
}
