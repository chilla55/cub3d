/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:09:53 by skorte            #+#    #+#             */
/*   Updated: 2022/09/14 12:20:35 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_empty_line(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (line[0] != '\n')
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	free (line);
}

void	skip_lines(t_game *game, int fd, int lts)
{
	char	*line;
	int		i;

	i = 0;
	while (i < lts)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close (fd);
			game_exit(game, -1);
		}
		free (line);
		i++;
	}
}
