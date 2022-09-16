/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:27:36 by skorte            #+#    #+#             */
/*   Updated: 2022/09/16 21:42:46 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_game *game, int color, int x, int y)
{
	int	pixel;

	pixel = (y * game->line_bytes) + (x * 4);
	if (game->endian == 1)
	{
		game->buffer[pixel + 0] = (color >> 24);
		game->buffer[pixel + 1] = (color >> 16) & 0xFF;
		game->buffer[pixel + 2] = (color >> 8) & 0xFF;
		game->buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (game->endian == 0)
	{
		game->buffer[pixel + 0] = (color) & 0xFF;
		game->buffer[pixel + 1] = (color >> 8) & 0xFF;
		game->buffer[pixel + 2] = (color >> 16) & 0xFF;
		game->buffer[pixel + 3] = (color >> 24);
	}
	return ;
}

static void	draw_minimap(t_game *game)
{
	int	color;
	int	color_2;
	int	color_3;
	int	x;
	int	y;

	color = 0x0BCDEF;
	color_2 = 0x123456;
	color_3 = 0x456789;
	x = 0;
	while (x < game->width * 10)
	{
		y = 0;
		while (y < game->height * 10)
		{
			if (y / 2 == (int)(game->y_pos * 10 / 2)
				&& x / 2 == (int)(game->x_pos * 10 / 2))
				draw_pixel(game, color, x, y);
			else if (y / 2 == (int)(game->rays[640]->y * 10 / 2)
				&& x / 2 == (int)(game->rays[640]->x * 10 / 2))
				draw_pixel(game, 0xEFCDAB, x, y);
			else if ((game->map[y / 10][x / 10]) == '1')
				draw_pixel(game, color_2, x, y);
			else
				draw_pixel(game, color_3, x, y);
			y++;
		}
		x++;
	}
}

void	fill_buffer(t_game *game)
{
	int	color;
	int	color_3;
	int	color_N;
	int	color_S;
	int	color_W;
	int	color_E;
	int	x;
	int	y;

	color = 0xABCDEF;
	color_3 = 0x456789;
	color_N = 0x0234F6;
	color_S = 0x423096;
	color_W = 0x823846;
	color_E = 0xB23B06;
	x = 0;
	while (x < X_RES)
	{
		y = 0;
		while (y < Y_RES)
		{
			if (y < Y_RES / 2 - game->rays[x]->height)
				draw_pixel(game, color, x, y);
			else if (y >= Y_RES / 2 - game->rays[x]->height
				&& y < Y_RES / 2 + game->rays[x]->height)
			{
				if (game->rays[x]->wallface == 'N')
					draw_pixel(game, color_N, x, y);
				else if (game->rays[x]->wallface == 'S')
					draw_pixel(game, color_S, x, y);
				else if (game->rays[x]->wallface == 'W')
					draw_pixel(game, color_W, x, y);
				else
					draw_pixel(game, color_E, x, y);
			}
			else
				draw_pixel(game, color_3, x, y);
			y++;
		}
		x++;
	}
	draw_minimap(game);
}

/*
** On expose events, the whole map gets redrawn.
*/

int	win_redraw(void *game_void)
{
	t_game	*game;

	game = ((t_game *)game_void);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	return (0);
}

static void	buffer_init(t_game *game)
{
	game->buffer = mlx_get_data_addr(game->frame_buffer,
			&game->pixel_bits, &game->line_bytes, &game->endian);
}

/*
** The mlx window, hooks and loops are set up here
*/

void	game_mlx_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, -2);
	game->mlx_win = mlx_new_window
		(game->mlx, X_RES, Y_RES, "Cub3D");
//	mlx_do_key_autorepeatoff(game->mlx);
	mlx_expose_hook(game->mlx_win, win_redraw, game);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_hook, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), exitclick, game);
	load_images(game);
	load_start_screen(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	sleep (1);
	buffer_init(game);
	fill_buffer(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	mlx_loop(game->mlx);
}
