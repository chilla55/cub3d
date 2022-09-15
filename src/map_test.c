/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:47:07 by skorte            #+#    #+#             */
/*   Updated: 2022/09/14 12:43:35 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
			{
				if (i == 0 || j == 0 || i == game->height - 1
					|| j == (int)ft_strlen(game->map[i]) - 1)
					game_exit(game, -1);
				if (ft_strchr(" \n", game->map[i + 1][j]) ||
					ft_strchr(" \n", game->map[i - 1][j]) ||
					ft_strchr(" \n", game->map[i][j + 1]) ||
					ft_strchr(" \n", game->map[i][j - 1]))
					game_exit(game, -1);
				if (game->map[i][j] != '0')
					p++;
			}
			set_player_pos(game, i, j);
			j++;
		}
		i++;
	}
	if (p != 1)
		game_exit(game, -1);
	printf("Map ok.\n");
}
