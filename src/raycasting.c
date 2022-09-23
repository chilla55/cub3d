/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 09:55:42 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray_set_alpha(t_game *game, int ray);
static void	ray_set_next_int(t_game *game, int ray);
static void	ray_set_height(t_game *game, int ray);

void	raycasting(t_game *game)
{
	int	ray;

	ray = 0;
	while (ray < X_RES)
	{
		ray_set_alpha(game, ray);
		ray_set_next_int(game, ray);
		ray_find_wall(game, ray);
		ray_set_height(game, ray);
		ray++;
	}
}

static void	ray_set_alpha(t_game *game, int ray)
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

static void	ray_set_next_int(t_game *game, int ray)
{
	game->rays[ray]->x = floor(game->x_pos) + game->rays[ray]->d_x_sign;
	game->rays[ray]->y = floor(game->y_pos) + game->rays[ray]->d_y_sign;
}

static void	ray_set_height(t_game *game, int ray)
{
	game->rays[ray]->height = (int)(Y_RES / 2.3 / game->rays[ray]->distance
			/ cos(game->rays[ray]->alpha_0));
}
