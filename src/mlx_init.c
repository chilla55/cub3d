/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:41:39 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 19:26:19 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	fill_buffer(t_game *game)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(game->frame_buffer, &pixel_bits, &line_bytes, &endian);
	int color = 0xABCDEF;
	int color_2 = 0x123456;
	int color_3 = 0x456789;
	for(int x = 0; x < X_RES; ++x)
	for(int y = 0; y < Y_RES; ++y)
	{
		int pixel = (y * line_bytes) + (x * 4);

		if (y < Y_RES / 2 - game->rays[x]->height)
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
				buffer[pixel + 3] = (color >> 24);
			}
		}
		else if (y >= Y_RES / 2 - game->rays[x]->height &&
			y < Y_RES / 2 + game->rays[x]->height )
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color_2 >> 24);
				buffer[pixel + 1] = (color_2 >> 16) & 0xFF;
				buffer[pixel + 2] = (color_2 >> 8) & 0xFF;
				buffer[pixel + 3] = (color_2) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color_2) & 0xFF;
				buffer[pixel + 1] = (color_2 >> 8) & 0xFF;
				buffer[pixel + 2] = (color_2 >> 16) & 0xFF;
				buffer[pixel + 3] = (color_2 >> 24);
			}
		}
		else
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color_3 >> 24);
				buffer[pixel + 1] = (color_3 >> 16) & 0xFF;
				buffer[pixel + 2] = (color_3 >> 8) & 0xFF;
				buffer[pixel + 3] = (color_3) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color_3) & 0xFF;
				buffer[pixel + 1] = (color_3 >> 8) & 0xFF;
				buffer[pixel + 2] = (color_3 >> 16) & 0xFF;
				buffer[pixel + 3] = (color_3 >> 24);
			}
		}
	}
}

/*
** On expose events, the whole map gets redrawn.
*/

int		win_redraw(void *game_void)
{
	t_game	*game;

	game = ((t_game *)game_void);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	return (0);	
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
	sleep (5);

	int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(game->frame_buffer, &pixel_bits, &line_bytes, &endian);
	int color = 0xABCDEF;
	int color_2 = 0x123456;
	int color_3 = 0x456789;
	for(int x = 0; x < X_RES; ++x)
	for(int y = 0; y < Y_RES; ++y)
	{
		int pixel = (y * line_bytes) + (x * 4);

		if (y < Y_RES / 2 - game->rays[x]->height)
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color >> 24);
				buffer[pixel + 1] = (color >> 16) & 0xFF;
				buffer[pixel + 2] = (color >> 8) & 0xFF;
				buffer[pixel + 3] = (color) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
				buffer[pixel + 3] = (color >> 24);
			}
		}
		else if (y >= Y_RES / 2 - game->rays[x]->height &&
			y < Y_RES / 2 + game->rays[x]->height )
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color_2 >> 24);
				buffer[pixel + 1] = (color_2 >> 16) & 0xFF;
				buffer[pixel + 2] = (color_2 >> 8) & 0xFF;
				buffer[pixel + 3] = (color_2) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color_2) & 0xFF;
				buffer[pixel + 1] = (color_2 >> 8) & 0xFF;
				buffer[pixel + 2] = (color_2 >> 16) & 0xFF;
				buffer[pixel + 3] = (color_2 >> 24);
			}
		}
		else
		{
			if (endian == 1)        // Most significant (Alpha) byte first
			{
				buffer[pixel + 0] = (color_3 >> 24);
				buffer[pixel + 1] = (color_3 >> 16) & 0xFF;
				buffer[pixel + 2] = (color_3 >> 8) & 0xFF;
				buffer[pixel + 3] = (color_3) & 0xFF;
			}
			else if (endian == 0)   // Least significant (Blue) byte first
			{
				buffer[pixel + 0] = (color_3) & 0xFF;
				buffer[pixel + 1] = (color_3 >> 8) & 0xFF;
				buffer[pixel + 2] = (color_3 >> 16) & 0xFF;
				buffer[pixel + 3] = (color_3 >> 24);
			}
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	mlx_loop(game->mlx);
}
