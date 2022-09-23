/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:47:07 by skorte            #+#    #+#             */
/*   Updated: 2022/09/23 10:30:30 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_surrounding(t_game *game, int i, int j);

/*
** Tests if the cubfile contains a valid map.
** Only allowed characters?
** Exactly one player position 'NWES' is mandatory.
** Tests if surrounded by '1'.
*/

void	map_test(t_game *game)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < (int)ft_strlen(game->map[i]))
		{
			if (!ft_strchr("10NWSE \n\0", game->map[i][j]))
				game_exit(game, -1);
			if (ft_strchr("0NWSE", game->map[i][j]))
				check_surrounding(game, i, j);
			if (ft_strchr("NWSE", game->map[i][j]))
				p++;
			set_player_pos(game, i, j);
			j++;
		}
		i++;
	}
	if (p != 1)
		game_exit(game, -1);
	printf("Map ok.\n");
}

static void	check_surrounding(t_game *game, int i, int j)
{
	if (i == 0 || j == 0 || i == game->height - 1
		|| j == (int)ft_strlen(game->map[i]) - 1)
		game_exit(game, -1);
	if (ft_strchr(" \n", game->map[i + 1][j]) ||
		ft_strchr(" \n", game->map[i - 1][j]) ||
		ft_strchr(" \n", game->map[i][j + 1]) ||
		ft_strchr(" \n", game->map[i][j - 1]))
		game_exit(game, -1);
}
