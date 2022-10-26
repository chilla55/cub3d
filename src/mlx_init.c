/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:27:36 by skorte            #+#    #+#             */
/*   Updated: 2022/10/25 21:54:00 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

/*
** Initializes the frame buffer.
*/

static void	buffer_init(t_game *game)
{
	mlx_destroy_image(game->mlx, game->frame_buffer);
	game->frame_buffer = mlx_new_image(game->mlx, X_RES, Y_RES);
	game->buffer = malloc(sizeof(t_buff));
	if (!game->buffer)
		game_exit(game, -4);
	game->buffer->buffer = mlx_get_data_addr(game->frame_buffer,
			&game->buffer->pixel_bits,
			&game->buffer->line_bytes,
			&game->buffer->endian);
}

/*
** The mlx window, hooks and loops are set up here.
*/

void	game_mlx_init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		game_exit(game, -2);
	game->mlx_win = mlx_new_window
		(game->mlx, X_RES, Y_RES, "Cub3D");
	load_start_screen(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->frame_buffer, X_RES / 2 - 640, Y_RES / 2 - 360);
	mlx_do_key_autorepeaton(game->mlx);
	mlx_expose_hook(game->mlx_win, win_redraw, game);
	load_images(game);
	buffer_init(game);
	fill_buffer(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_hook, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), exitclick, game);
	mlx_loop(game->mlx);
}
