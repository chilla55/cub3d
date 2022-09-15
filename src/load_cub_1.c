/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:07:21 by skorte            #+#    #+#             */
/*   Updated: 2022/09/14 12:20:25 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_size(t_game *game, int fd)
{
	char	*line;

	game->height = 1;
	game->width = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->height++;
		if (game->height >= 0 && (int)ft_strlen(line) > game->width)
		{
			game->width = (int)ft_strlen(line);
			if (line[ft_strlen(line) - 1 == '\n'])
				game->width--;
		}
		free(line);
		line = get_next_line(fd);
	}
	printf("map size: %i x %i\n", game->width, game->height);
	return ;
}
