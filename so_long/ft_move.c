/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:56:32 by skorte            #+#    #+#             */
/*   Updated: 2022/04/07 12:53:59 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Tests if win or caught condition is met.
** Is called by ft_move_p and ft_move_g.
** Sets exitmode accordingly.
*/

static int	ft_test(t_map *map)
{
	if (map->p_pos == map->g_pos
		|| map->p_pos == map->g_pos + 1
		|| map->p_pos == map->g_pos - 1
		|| map->p_pos == map->g_pos + (map->width + 1)
		|| map->p_pos == map->g_pos - (map->width + 1))
	{
		ft_t_map_print(map);
		ft_redraw_g(map);
		ft_redraw_p(map);
		map->exitmode = 2;
	}
	if (map->tiles[map->p_pos] == 'E' && !ft_strchr(map->tiles, 'C'))
		map->exitmode = 1;
	return (map->exitmode);
}

/*
** If compiled with GUARD = 1, a guard will roam the map
** and kill the player on contact.
** ft_move_g executes the game logic of a guard move.
**
** The guard always moves, never gets stuck at walls or objects.
** If a key input cannot result in a step, a new key is generated
** and ft_move_g calls itself again.
*/

void	ft_move_g(t_map *map, int key)
{
	if (!map->g_pos || map->exitmode != 0)
		return ;
	map->g_old = map->g_pos;
	if (key == 'w')
		map->g_pos = map->g_pos - (map->width + 1);
	else if (key == 'a')
		map->g_pos = map->g_pos - 1;
	else if (key == 's')
		map->g_pos = map->g_pos + (map->width + 1);
	else if (key == 'd')
		map->g_pos = map->g_pos + 1;
	if (ft_strchr("1CE", map->tiles[map->g_pos]))
	{
		map->last_guard_move--;
		map->g_pos = map->g_old;
		key = ft_input_generator(map);
		ft_move_g(map, key);
		return ;
	}
	map->tiles[map->g_old] = '0';
	map->tiles[map->g_pos] = 'G';
	ft_test(map);
}

/*
** On key press events, ft_move_p is called.
** It moves the player on the map according to the input.
** The graphical window is updated at the end,
** and the step count displayed.
*/

void	ft_move_p(t_map *map, int key)
{
	if (map->exitmode != 0)
		return ;
	map->p_old = map->p_pos;
	if (key == 'w')
		map->p_pos = map->p_pos - (map->width + 1);
	else if (key == 'a')
		map->p_pos = map->p_pos - 1;
	else if (key == 's')
		map->p_pos = map->p_pos + (map->width + 1);
	else if (key == 'd')
		map->p_pos = map->p_pos + 1;
	if ((map->tiles[map->p_pos] == 'E' && ft_strchr(map->tiles, 'C'))
		|| (map->tiles[map->p_pos] == '1'))
	{
		map->p_pos = map->p_old;
		return ;
	}
	map->steps++;
	map->tiles[map->p_old] = '0';
	if (!ft_test(map))
		map->tiles[map->p_pos] = 'P';
	ft_redraw_p(map);
	ft_redraw_0(map, map->p_old);
	ft_draw_step_count(map);
}

/*
** To move a guard, an input generator is used to generate "wasd"
** like key events for the player.
** It generates a new key once a second.
**
** In 3 of 4 cases, the last move is repeated if possible.
** Otherwise a random key is chosen.
*/

int	ft_input_generator(t_map *map)
{
	char	c;
	char	keys[4];
	int		lastmove;

	if (map->g_pos == 0 || map->exitmode != 0
		|| map->last_guard_move == time(NULL))
		return (0);
	ft_strlcpy(keys, "wasd", 5);
	lastmove = map->g_pos - map->g_old;
	c = keys[rand() % 4];
	if (lastmove && rand() % 4)
	{
		if (lastmove < -1)
			c = keys[0];
		else if (lastmove == -1)
			c = keys[1];
		else if (lastmove > 1)
			c = keys[2];
		if (lastmove == 1)
			c = keys[3];
	}
	map->g_key = (int)c;
	map->last_guard_move = time(NULL);
	return (map->g_key);
}

/*
** On map initialization, if compiled with GUARD = 1,
** a guard will be randomly placed on the map.
** (if not already present in the .ber file)
** Only positions of "0" background with at least 1 tile distance
** to the player's start position are allowed.
** If no such position can be found, no guard is placed.
*/

void	ft_guard_pos_generator(t_map *map)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (map->tiles[i])
	{	
		if (map->tiles[i] == '0' && map->p_pos != i + 1 && map->p_pos != i - 1
			&& map->p_pos != i + (map->width + 1)
			&& map->p_pos != i - (map->width + 1))
			break ;
		i++;
	}
	if (i != (int)ft_strlen(map->tiles))
	{
		while (map->tiles[pos] != '0'
			|| map->p_pos == pos + 1 || map->p_pos == pos - 1
			|| map->p_pos == pos + (map->width + 1)
			|| map->p_pos == pos - (map->width + 1))
			pos = rand() % ft_strlen(map->tiles);
		map->tiles[pos] = 'G';
	}
	map->g_pos = pos;
	map->g_old = pos;
}
