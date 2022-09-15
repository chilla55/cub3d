/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 22:19:21 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_x_wall(t_game *game, double x, double d_x, double alpha);
static int	check_y_wall(t_game *game, double x, double d_x, double alpha);
static double	raycast_find_wall(t_game *game, int ray);
void	ray_set_alpha(t_game *game, int ray);


void	raycasting(t_game *game)
{
	int	ray;

	ray = 0;
	while (ray < X_RES)
	{
		ray_set_alpha(game, ray);
		game->rays[ray]->x = floor(game->x_pos) + game->rays[ray]->d_x_sign;
		game->rays[ray]->y = floor(game->y_pos) + game->rays[ray]->d_y_sign;

		game->rays[ray]->distance = raycast_find_wall(game, ray);
		game->rays[ray]->height = (int)(Y_RES / 2 / game->rays[ray]->distance);
		ray++;
	}
}

double	raycast_find_wall(t_game *game, int ray)
{
	double	d_x;
	double	d_y;
	double	x = game->rays[ray]->x;
	double	y = game->rays[ray]->y;

	d_x = (x - game->x_pos) / sin(game->rays[ray]->alpha);
	if (d_x < 0)
		d_x *= -1;
	d_y = (y - game->y_pos) / cos(game->rays[ray]->alpha);
	if (d_y < 0)
		d_y *= -1;
	if (d_x <= d_y)
	{
		if (check_x_wall(game, x, d_x, game->rays[ray]->alpha))
		{
			game->rays[ray]->y = game->y_pos - d_x * cos (game->rays[ray]->alpha);
			return (d_x);
		}
		if (x > game->x_pos)
			game->rays[ray]->x = x + 1.0;
		else
			game->rays[ray]->x = x - 1.0;
	}
	else
	{
		if (check_y_wall(game, y, d_y, game->rays[ray]->alpha))
		{
			game->rays[ray]->x = game->x_pos + d_y * sin (game->rays[ray]->alpha);
			return (d_y);
		}
		if (y > game->y_pos)
			game->rays[ray]->y = y + 1.0;
		else
			game->rays[ray]->y = y - 1.0;
	}
	return (raycast_find_wall(game, ray));
}

int	check_x_wall(t_game *game, double x, double d_x, double alpha)
{
	double	y;

	y = game->y_pos - d_x * cos (alpha); //+ d_x * sin (alpha);
	if (game->map[(int)ceil(y)][(int)ceil(x)] == '1')
		return (1);
	return (0);
}

int	check_y_wall(t_game *game, double y, double d_y, double alpha)
{
	double	x;

	x = game->x_pos + d_y * sin (alpha);
	if (game->map[(int)ceil(y)][(int)ceil(x)] == '1')
		return (1);
	return (0);
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

