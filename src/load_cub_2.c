/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:09:53 by skorte            #+#    #+#             */
/*   Updated: 2022/09/05 18:25:48 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_f_color(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "F ", 2))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->f_color = ft_substr(line, 2, ft_strlen(line) - 3);
	free (line);
}

void	get_c_color(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "C ", 2))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->c_color = ft_substr(line, 2, ft_strlen(line) - 3);
	free (line);
}

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

void	skip_lines(t_game *game, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 8)
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
