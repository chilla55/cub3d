/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:41:39 by skorte            #+#    #+#             */
/*   Updated: 2022/09/07 22:58:10 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** key_hook defines the action that happens upon key-down events.
** The escape key (key code 65307) triggers the program to exit.
*/

static int	key_hook(int key, void *game_void)
{
	t_game	*game;

	game = ((t_game *)game_void);
	if (key == 65307) // ESC key in UNIX
		game_exit (game, 65307);
	if (key == 65361) // left arrow in UNIX
	{
		game->angle -=5;
		key = '<';
	}
	if (key == 65363) // right arrow in UNIX
		{
		game->angle +=5;
		key = '>';
	}
	if (ft_strchr("wasd<>", key))
	{
		write(1, "\r", 1);
		write(1, &key, 1);
	}
	return (0);
}

/*
** The loop waits 30 ms, so runs with up to 33 fps.
** It only redraws the necessary tiles (player, guard, their old positions).
** If map->redraw is set to 1 (e.g. fresh start or window moved)
** the whole window is redrawn.
** If a guard is present, it is moved once a second.
** The animations to make random stars twinkle and cats wink is run.
** A string with the number of steps is printed in the upper left corner
** of the window.
*/

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

static int	game_loop(void *game_void)
{
	t_game	*game;

	game = ((t_game *)game_void);
	int	i = 0;
	printf("\nCalculating current ray directions\n");
	while (i < X_RES)
	{
//		raycast_ray_init(game, i);
		game->rays[i]->distance = raycast_ray_init(game, i);
		game->rays[i]->height = (int)(Y_RES / 2 / game->rays[i]->distance);
		i++;
	}
	fill_buffer(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->frame_buffer, 0, 0);
//	if (map->redraw == 1)
//		ft_mlx_draw_map(map);
//	map->redraw = 0;
//	{
//		if (ft_input_generator(map))
//		{
	// 		ft_move_g(map, map->g_key);
	// 		ft_t_map_print(map);
	// 		ft_redraw_g(map);
	// 	}
	// 	ft_redraw_p(map);
	// 	ft_twinkle_animation(map);
	// }
	return (0);
}


/*
** All tiles of the map are drawn into the window.
** This is done on startup and on expose events.
*/

/*
void	ft_mlx_draw_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < (int)ft_strlen(map->tiles))
	{
		if (map->tiles[i] == 'P')
			ft_redraw_p(map);
		else if (map->tiles[i] == 'G')
			ft_redraw_g(map);
		else if (map->tiles[i] == '0')
			ft_redraw_0(map, i);
		else if (map->tiles[i] == '1')
			ft_redraw_1(map, i);
		else if (map->tiles[i] == 'C')
			ft_redraw_c(map, i);
		else if (map->tiles[i] == 'E')
			ft_put_image_2(map->e[0], i, map);
		i++;
	}
	if (map->steps)
		ft_draw_step_count(map);
}
*/

/*
** On expose events, the whole map gets redrawn.
*/

/*
int	ft_win_redraw(void *map_void)
{
	t_map	*map;

	map = ((t_map *)map_void);
	map->redraw = 1;
	return (0);
}
*/

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
//	mlx_do_key_autorepeatoff(game->mlx);0
//	mlx_expose_hook(game->mlx_win, ft_win_redraw, game);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_hook, game);
	mlx_hook(game->mlx_win, 17, (1L << 17), exitclick, game);
	load_images(game);
	load_start_screen(game);

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
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}
