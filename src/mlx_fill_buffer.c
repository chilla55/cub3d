/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fill_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:53:57 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 10:56:27 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_minimap(t_game *game);
static void	draw_crosshair(t_game *game);
static int	get_tex_pixel(t_game *game, int x, int y);
static int	get_wallface_index(char wallface);

void	fill_buffer(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < Y_RES)
	{
		x = 0;
		while (x < X_RES)
		{
			if (y < Y_RES / 2 - game->rays[x]->height)
				draw_pixel(game->buffer, game->c_color, x, y);
			else if (y >= Y_RES / 2 - game->rays[x]->height
				&& y < Y_RES / 2 + game->rays[x]->height)
				draw_pixel(game->buffer, get_tex_pixel(game, x, y), x, y);
			else
				draw_pixel(game->buffer, game->f_color, x, y);
			x++;
		}
		y++;
	}
	draw_minimap(game);
	draw_crosshair(game);
}

static void	draw_minimap(t_game *game)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < game->width * 10)
	{
		y = 0;
		while (y < game->height * 10)
		{
			if (y / 2 == (int)(game->y_pos * 10 / 2)
				&& x / 2 == (int)(game->x_pos * 10 / 2))
				color = 0x0BCDEF;
			else if (y / 2 == (int)(game->rays[(int)(X_RES / 2)]->y * 10 / 2)
				&& x / 2 == (int)(game->rays[(int)(X_RES / 2)]->x * 10 / 2))
				color = 0xEFCDAB;
			else if ((game->map[y / 10][x / 10]) == '1')
				color = 0x123456;
			else
				color = 0x456789;
			draw_pixel(game->buffer, color, x, y);
			y++;
		}
		x++;
	}
}

static void	draw_crosshair(t_game *game)
{
	int		x;
	int		y;
	int		x_size;
	double	radius;

	x_size = 40;
	x = X_RES / 2 - x_size;
	while (x <= X_RES / 2 + x_size)
	{
		y = Y_RES / 2 - x_size;
		while (y <= Y_RES / 2 + x_size)
		{
			radius = (pow((x - X_RES / 2), 2) + pow((y - Y_RES / 2), 2));
			if ((int)sqrt(radius) / 2 == (int)(x_size * 0.75) / 2
				|| (int)sqrt(radius) <= (int)(x_size * 0.1))
				draw_pixel(game->buffer, 0xEFCDAB, x, y);
			else if (x / 2 == (int)(X_RES / 4) || y / 2 == (int)(Y_RES / 4))
				draw_pixel(game->buffer, 0xFF0000, x, y);
			y++;
		}
		x++;
	}
}

static int	get_tex_pixel(t_game *game, int ray, int hor_line)
{
	int		y;
	double	y_frac;
	int		x;

	y_frac = ((double)hor_line - ((double)Y_RES / 2
				- (double)game->rays[ray]->height)) / 2
		/ (double)game->rays[ray]->height;
	y = (int)floor((double)TILE_SIZE * y_frac);
	x = 0;
	if (game->rays[ray]->wallface == 'N'
		|| game->rays[ray]->wallface == 'S')
		x = (int)((double)TILE_SIZE
				* (game->rays[ray]->y - floor(game->rays[ray]->y)));
	else
		x = (int)((double)TILE_SIZE
				* (game->rays[ray]->x - floor(game->rays[ray]->x)));
	if (0 <= y && y < TILE_SIZE)
	{
		return (extract_pixel(game->textures
				[get_wallface_index(game->rays[ray]->wallface)], x, y));
	}
	return (0);
}

static int	get_wallface_index(char wallface)
{
	if (wallface == 'N')
		return (0);
	if (wallface == 'E')
		return (1);
	if (wallface == 'N')
		return (2);
	return (3);
}
