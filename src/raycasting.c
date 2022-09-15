/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 21:14:20 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	X_RES rays, equally??? spaced between angle-45 to angle+45 - No, not equally...
	each needs distance to wall, type of wall face (NSWE),
	and point on wall (between 0 and 1 to extract from texture)
*/
void	raycaster_cal_default_angles(t_game *game)
{
	int		i;

	i = 0;
	while (i < X_RES)
	{
		game->rays[i] = malloc(sizeof(t_ray));
		game->rays[i]->alpha_0 = atan(((double)i + 0.5 - (double)X_RES / 2.0)
				/ ((double)X_RES / 2.0));
		i++;
	}
}

void	raycasting(t_game *game)
{
	int	i;
	
	i = 0;
	while (i < X_RES)
	{
		game->rays[i]->distance = raycast_ray_init(game, i);
		game->rays[i]->height = (int)(Y_RES / 2 / game->rays[i]->distance);
		i++;	
	}
}


void	raycaster_init(t_game *game)
{
	int		i;

	i = 0;
	while (i < X_RES)
	{
		game->rays[i] = malloc(sizeof(t_ray));
		if (game->rays[i] == NULL)
			game_exit(game, -10);  // exitmode not defined yet
		i++;
	}
	raycaster_cal_default_angles(game);
	raycasting(game);
}

int	check_x_wall(t_game *game, double x, double d_x, double alpha)
{
	double	y;

	y = game->y_pos + d_x * sin (alpha);
	if (game->map[(int)ceil(y)][(int)ceil(x)] == '1')
		return (1);
	return (0);}

int	check_y_wall(t_game *game, double y, double d_y, double alpha)
{
	double	x;

	x = game->x_pos + d_y * cos (alpha);
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
}
