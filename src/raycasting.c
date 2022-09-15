/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 19:34:54 by skorte           ###   ########.fr       */
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
	printf("\nCalculating default ray directions (only needs to be once done at the beginning)\n");
	while (i < X_RES)
	{
		game->rays[i] = malloc(sizeof(t_ray));
		game->rays[i]->alpha_0 = atan(((double)i + 0.5 - (double)X_RES / 2.0)
				/ ((double)X_RES / 2.0));
		printf("%f \n", cal_degree(game->rays[i]->alpha_0));
		i++;
	}
	i = 0;
	while (i < X_RES)
	{
//		raycast_ray_init(game, i);
		game->rays[i]->distance = raycast_ray_init(game, i);
		game->rays[i]->height = (int)(Y_RES / 2 / game->rays[i]->distance);
		i++;	
	}
}

int	check_x_wall(t_game *game, double x, double d_x, double alpha)
{
	double	y;

	y = game->y_pos + d_x * sin (alpha);
//	printf("checking map: %f %f %i \n", x, y, game->map[(int)ceil(y)][(int)ceil(x)]);
	if (game->map[(int)ceil(y)][(int)ceil(x)] == '1')
		return (1);
	return (0);}

int	check_y_wall(t_game *game, double y, double d_y, double alpha)
{
	double	x;

	x = game->x_pos + d_y * cos (alpha);
//	printf("checking map: %f %f %i \n", x, y, game->map[(int)ceil(y)][(int)ceil(x)]);
	if (game->map[(int)ceil(y)][(int)ceil(x)] == '1')
		return (1);
	return (0);
}

double	raycast_find_wall(t_game *game, double x, double y, int ray)
{
	double	d_x;
	double	d_y;

	d_x = (x - game->x_pos) / sin(game->rays[ray]->alpha);
	if (d_x < 0)
		d_x *= -1;
	d_y = (y - game->y_pos) / cos(game->rays[ray]->alpha);
	if (d_y < 0)
		d_y *= -1;
//	printf(" dx %f dy %f ", d_x, d_y);
	if (d_x <= d_y)
	{
		if (check_x_wall(game, x, d_x, game->rays[ray]->alpha))
			return (d_x);
		if (x > game->x_pos)
			x = x + 1.0;
		else
			x = x - 1.0;
	}
	else
	{
		if (check_y_wall(game, y, d_y, game->rays[ray]->alpha))
			return (d_y);
		if (y > game->y_pos)
			y = y + 1.0;
		else
			y = y - 1.0;
	}
//	printf (" new x %f y %f \n", x, y);
	return (raycast_find_wall(game, x, y, ray));
}

void	ray_set_alpha(t_game *game, int ray)
{
	game->rays[ray]->alpha = game->rays[ray]->alpha_0 + cal_radian(game->angle);
	while (game->rays[ray]->alpha < 0)
		game->rays[ray]->alpha += 2 * PI;
	while (game->rays[ray]->alpha >= 2 * PI)
		game->rays[ray]->alpha -= 2 * PI;
	game->rays[ray]->d_x_sign = NEG_SIGN;
	if (0 < game->rays[ray]->alpha && game->rays[ray]->alpha <= PI)
		game->rays[ray]->d_x_sign = POS_SIGN;
	game->rays[ray]->d_y_sign = NEG_SIGN;
	if (PI / 2 < game->rays[ray]->alpha && game->rays[ray]->alpha <= 3 * PI / 2)
		game->rays[ray]->d_y_sign = POS_SIGN;
	return ;
}

double	raycast_ray_init(t_game *game, int ray)
{
	double	x;
	double	y;

	ray_set_alpha(game, ray);
	x = floor(game->x_pos) + game->rays[ray]->d_x_sign;
	y = floor(game->y_pos) + game->rays[ray]->d_y_sign;
	return (raycast_find_wall(game, x, y, ray));
	return (game->rays[ray]->alpha);
}
