/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_draw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:29:04 by skorte            #+#    #+#             */
/*   Updated: 2022/04/07 12:46:17 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Randomly redraws a background tile with a random twinkle to it.
** Redraws every 15th collectible once per look with a random new one.
*/

void	ft_twinkle_animation(t_map *map)
{
	int	pos;
	int	twinkle_pos;

	pos = 0;
	while (map->tiles[pos])
	{
		if (map->tiles[pos] == 'C' && !(rand() % 15))
			ft_redraw_c(map, pos);
		pos++;
	}
	twinkle_pos = 0;
	while (map->tiles[twinkle_pos] != '0')
		twinkle_pos = rand() % ft_strlen(map->tiles);
	ft_redraw_0(map, twinkle_pos);
}

/*
** Basic procedure to put an image to a tile in the window.
*/

void	ft_put_image_2(void *img, int pos, t_map *map)
{
	int	x;
	int	y;

	x = pos % (map->width + 1) * TILE_SIZE;
	y = (pos / (map->width + 1)) * TILE_SIZE;
	mlx_put_image_to_window(map->mlx, map->mlx_win, img, x, y);
}

/*
** In case of winning, the exit tile is rendered
** according to player motion direction.
*/

void	ft_draw_win(t_map *map)
{
	if (map->p_key == 'w')
		ft_put_image_2(map->w[2], map->p_pos, map);
	else if (map->p_key == 'a')
		ft_put_image_2(map->w[1], map->p_pos, map);
	else if (map->p_key == 's')
		ft_put_image_2(map->w[3], map->p_pos, map);
	else if (map->p_key == 'd')
		ft_put_image_2(map->w[0], map->p_pos, map);
	if (map->p_old != map->p_pos)
		ft_redraw_0(map, map->p_old);
	map->anim_counter++;
	if (map->anim_counter > 20)
		ft_exit(map, 1);
}

/*
** If caught by the guard, a 7-frame animation of an explosion is displayed
** at the player position with a frame rate of loop/6 ~ 5 fps
*/

void	ft_draw_caught(t_map *map)
{
	int	img_num;

	if (map->p_old != map->p_pos)
		ft_redraw_0(map, map->p_old);
	if (map->anim_counter <= 36)
		img_num = map->anim_counter / 6;
	else
		img_num = 6;
	ft_put_image_2(map->x[img_num], map->p_pos, map);
	map->anim_counter++;
	if (map->anim_counter > 100)
		ft_exit(map, 2);
}

/*
** The step count is written to the upper left edge of the mlx window.
** Therefore the underlying tile is redrawn every time the step count changes.
*/

void	ft_draw_step_count(t_map *map)
{
	char	*step_str;

	step_str = ft_itoa(map->steps);
	ft_redraw_1(map, 0);
	mlx_string_put(map->mlx, map->mlx_win, 8, 16, 255, step_str);
	free(step_str);
}
