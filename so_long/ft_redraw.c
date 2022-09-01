/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redraw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:15:10 by skorte            #+#    #+#             */
/*   Updated: 2022/04/03 16:37:42 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Renders the background on position 'pos'
** There are 4 x 4 different tiles. Which one is used depends on pos % 4 for
** the tile group and random for the twinkle level.
*/

void	ft_redraw_0(t_map *map, int pos)
{
	if (map->tiles[pos] != '0')
		return ;
	ft_put_image_2(map->o[(pos % 4) * 4 + (time(NULL)) % 4], pos, map);
}

/*
** Renders the wall on position 'pos'
** There are 4 different tiles. Which one is used depends on pos % 4.
*/

void	ft_redraw_1(t_map *map, int pos)
{
	if (map->tiles[pos] != '1')
		return ;
	if (pos == 0)
		ft_put_image_2(map->r[4], pos, map);
	else
		ft_put_image_2(map->r[pos % 4], pos, map);
}

/*
** Renders the cat-collectibles. A random state of
** the astrocat is drawn.
*/

void	ft_redraw_c(t_map *map, int pos)
{
	if (map->tiles[pos] != 'C')
		return ;
	ft_put_image_2(map->c[rand() % 4], pos, map);
}

/*
** The player is redrawn, oriented depending on the last keystroke.
** In case of winning or getting caught, the draw call gets forwarded
** to the appropriate function.
*/

void	ft_redraw_p(t_map *map)
{
	if (map->tiles[map->p_pos] == 'E')
		ft_draw_win(map);
	else if (map->exitmode == 2)
		ft_draw_caught(map);
	else if (map->p_key == 'w')
		ft_put_image_2(map->p[2], map->p_pos, map);
	else if (map->p_key == 'a')
		ft_put_image_2(map->p[1], map->p_pos, map);
	else if (map->p_key == 's')
		ft_put_image_2(map->p[3], map->p_pos, map);
	else if (map->p_key == 'd')
		ft_put_image_2(map->p[0], map->p_pos, map);
}

/*
** If present, the guard is redrawn.
** On movement, the former position gets filled with background again.
*/

void	ft_redraw_g(t_map *map)
{
	if (map->g_pos == 0)
		return ;
	if (map->g_old != map->g_pos)
		ft_redraw_0(map, map->g_old);
	if (map->g_key == 'w')
		ft_put_image_2(map->g[2], map->g_pos, map);
	else if (map->g_key == 'a')
		ft_put_image_2(map->g[1], map->g_pos, map);
	else if (map->g_key == 's')
		ft_put_image_2(map->g[3], map->g_pos, map);
	else if (map->g_key == 'd')
		ft_put_image_2(map->g[0], map->g_pos, map);
}
