/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:27:36 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 10:02:42 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_wallface_index(char wallface)
{
	if (wallface == 'N')
		return (0);
	if (wallface == 'E')
		return (1);
	if (wallface == 'N')
		return (2);
	return (3);
}

int	get_tex_pixel(t_game *game, int ray, int hor_line)
{
	int		y;
	double 	y_frac;
	int		x;

	y_frac = ((double)hor_line - ((double)Y_RES / 2 - (double)game->rays[ray]->height )) / 2 / (double)game->rays[ray]->height ;
	y = (int)floor((double)TILE_SIZE * y_frac);
	x = 0;
	if (game->rays[ray]->wallface == 'N' || game->rays[ray]->wallface == 'S')
		x = (int)((double)TILE_SIZE * (game->rays[ray]->y - floor(game->rays[ray]->y)));
	else
		x = (int)((double)TILE_SIZE * (game->rays[ray]->x - floor(game->rays[ray]->x)));
	if (0 <= y && y < TILE_SIZE)
	{
		return (extract_pixel(game->textures[get_wallface_index(game->rays[ray]->wallface)], x, y));
	}
	return (0);
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
				draw_pixel(game->buffer, color, x, y);
			else if (y / 2 == (int)(game->rays[(int)(X_RES / 2)]->y * 10 / 2)
				&& x / 2 == (int)(game->rays[(int)(X_RES / 2)]->x * 10 / 2))
				draw_pixel(game->buffer, 0xEFCDAB, x, y);
			else if ((game->map[y / 10][x / 10]) == '1')
				draw_pixel(game->buffer, color_2, x, y);
			else
				draw_pixel(game->buffer, color_3, x, y);
			y++;
		}
		x++;
	}
}

void	draw_crosshair(t_game *game)
{
	int	x;
	int		y;
	int		x_size;
	double	radius;

	x_size = 40;
	x = X_RES / 2 - x_size;
	while (x <= X_RES / 2 + x_size)
	{
		y = Y_RES / 2 - x_size;;
		while (y <= Y_RES / 2 + x_size)
		{
			radius = (pow((x - X_RES / 2), 2) + pow((y - Y_RES / 2), 2));
			if ((int)sqrt(radius) / 2 == (int)(x_size * 0.75) / 2
				|| (int)sqrt(radius) <=  (int)(x_size * 0.1))
				draw_pixel(game->buffer, 0xEFCDAB, x, y);
			else if (x / 2 == (int)(X_RES / 4) || y / 2 == (int)(Y_RES / 4))
				draw_pixel(game->buffer, 0xFF0000, x, y);
			y++;
		}
		x++;
	}
}

void	copy_texture(t_game *game)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < TILE_SIZE)
	{
		y = 0;
		while (y < TILE_SIZE)
		{
			color = extract_pixel(game->textures[0], x, y);
			draw_pixel(game->buffer, color, x, y);
			y++;
		}
		x++;
	}
}

/*
void	insert_vert_line(t_game *game, int x, int face)
{
	int y;

	y = 0;
	while (y < Y_RES)
	{
		draw_color_pixel(game, color_N + (int)((game->rays[x]->y - floor(game->rays[x]->y)) * 256 ), x, y);
	}
}
*/

void	fill_buffer(t_game *game)
{
	int	color;
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
			{
					color = get_tex_pixel(game, x, y);
					draw_pixel(game->buffer, color, x, y);
 			}
			else
				draw_pixel(game->buffer, game->f_color, x, y);
			x++;
		}
		y++;
	}
	draw_minimap(game);
	draw_crosshair(game);
//	copy_texture(game);
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

/*
** Initializes the frame buffer.
*/

static void	buffer_init(t_game *game)
{
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
