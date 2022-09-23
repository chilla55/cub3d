/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_find_wall.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 08:43:38 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 18:04:51 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_x_wall(t_game *game, t_ray *ray);
static int	check_y_wall(t_game *game, t_ray *ray);
static void	increment(t_game *game, int ray, char c);
static void	ray_set_wall(t_game *game, int ray, char c);

void	ray_find_wall(t_game *game, int ray)
{
	game->rays[ray]->d_x = fabs((game->rays[ray]->x - game->x_pos)
			/ sin(game->rays[ray]->alpha));
	game->rays[ray]->d_y = fabs((game->rays[ray]->y - game->y_pos)
			/ cos(game->rays[ray]->alpha));
	if (game->rays[ray]->d_x <= game->rays[ray]->d_y)
	{
		if (check_x_wall(game, game->rays[ray]))
		{
			ray_set_wall(game, ray, 'x');
			return ;
		}
		increment(game, ray, 'x');
		ray_find_wall(game, ray);
	}
	else
	{
		if (check_y_wall(game, game->rays[ray]))
		{
			ray_set_wall(game, ray, 'y');
			return ;
		}
		increment(game, ray, 'y');
		ray_find_wall(game, ray);
	}
}

static int	check_x_wall(t_game *game, t_ray *ray)
{
	double	y;

	y = game->y_pos - ray->d_x * cos (ray->alpha);
	if (game->map[(int)floor(y)][(int)floor(ray->x) - 1 + ray->d_x_sign] == '1')
		return (1);
	return (0);
}

static int	check_y_wall(t_game *game, t_ray *ray)
{
	double	x;

	x = game->x_pos + ray->d_y * sin (ray->alpha);
	if (game->map[(int)floor(ray->y) - 1 + ray->d_y_sign][(int)floor(x)] == '1')
		return (1);
	return (0);
}

static void	increment(t_game *game, int ray, char c)
{
	if (c == 'x')
	{
		if (game->rays[ray]->x > game->x_pos)
			game->rays[ray]->x = game->rays[ray]->x + 1.0;
		else
			game->rays[ray]->x = game->rays[ray]->x - 1.0;
	}
	else
	{
		if (game->rays[ray]->y > game->y_pos)
			game->rays[ray]->y = game->rays[ray]->y + 1.0;
		else
			game->rays[ray]->y = game->rays[ray]->y - 1.0;
	}
}

static void	ray_set_wall(t_game *game, int ray, char c)
{
	if (c == 'x')
	{
		if (game->rays[ray]->d_x_sign == 1)
			game->rays[ray]->wallface = 'E';
		else
			game->rays[ray]->wallface = 'W';
		game->rays[ray]->y = game->y_pos
			- game->rays[ray]->d_x * cos (game->rays[ray]->alpha);
		game->rays[ray]->distance = game->rays[ray]->d_x;
	}
	else
	{
		if (game->rays[ray]->d_y_sign == 1)
			game->rays[ray]->wallface = 'S';
		else
			game->rays[ray]->wallface = 'N';
		game->rays[ray]->x = game->x_pos
			+ game->rays[ray]->d_y * sin (game->rays[ray]->alpha);
		game->rays[ray]->distance = game->rays[ray]->d_y;
	}
}
