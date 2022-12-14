/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_fill_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 10:53:57 by skorte            #+#    #+#             */
/*   Updated: 2022/10/25 18:27:28 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_minimap(t_game *game);
static void		draw_crosshair(t_game *game);
static t_color	get_tex_pixel(t_game *game, int x, int y);
static int		get_wallface_index(char wallface);

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
	int		x;
	int		y;
	char	c;

	x = 0;
	while (x < game->width * game->scale)
	{
		y = 0;
		while (y < game->height * game->scale)
		{
			c = (game->map[(int)(y / game->scale)][(int)(x / game->scale)]);
			if (y / 2 == (int)(game->y_pos * game->scale / 2)
				&& x / 2 == (int)(game->x_pos * game->scale / 2))
				draw_pixel(game->buffer, getcolor(0, 11, 205, 239), x, y);
			else if (y / 2 == (int)(game->rays[X_RES / 2]->y * game->scale / 2)
				&& x / 2 == (int)(game->rays[X_RES / 2]->x * game->scale / 2))
				draw_pixel(game->buffer, getcolor(0, 239, 205, 171), x, y);
			else if (c == '1')
				draw_pixel(game->buffer, getcolor(0, 18, 52, 86), x, y);
			else if (c != ' ')
				draw_pixel(game->buffer, getcolor(0, 69, 103, 137), x, y);
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
				draw_pixel(game->buffer, getcolor(0, 239, 205, 171), x, y);
			else if (x / 2 == (int)(X_RES / 4) || y / 2 == (int)(Y_RES / 4))
				draw_pixel(game->buffer, getcolor(0, 255, 0, 0), x, y);
			y++;
		}
		x++;
	}
}

static t_color	get_tex_pixel(t_game *game, int ray, int hor_line)
{
	int		y;
	int		x;
	double	y_frac;
	double	x_frac;
	int		i;

	i = get_wallface_index(game->rays[ray]->wallface);
	y_frac = ((double)hor_line - ((double)Y_RES / 2
				- (double)game->rays[ray]->height)) / 2
		/ (double)game->rays[ray]->height;
	y = (int)floor(((double)(game->textures[i]->y_size)) * y_frac);
	if (game->rays[ray]->wallface == 'E')
		x_frac = (game->rays[ray]->y - floor(game->rays[ray]->y));
	else if (game->rays[ray]->wallface == 'W')
		x_frac = (ceil(game->rays[ray]->y) - game->rays[ray]->y);
	else if (game->rays[ray]->wallface == 'N')
		x_frac = (game->rays[ray]->x - floor(game->rays[ray]->x));
	else
		x_frac = (ceil(game->rays[ray]->x) - game->rays[ray]->x);
	x = (int)((double)game->textures[i]->x_size * x_frac);
	if (0 <= y && y < game->textures[i]->y_size)
		return (extract_pixel(game->textures[i], x, y));
	return (getcolor(0, 0, 0, 0));
}

static int	get_wallface_index(char wallface)
{
	if (wallface == 'N')
		return (0);
	if (wallface == 'S')
		return (1);
	if (wallface == 'W')
		return (2);
	return (3);
}
