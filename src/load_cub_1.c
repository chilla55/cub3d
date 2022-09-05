/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_cub_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:07:21 by skorte            #+#    #+#             */
/*   Updated: 2022/09/05 18:50:21 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_size(t_game *game, int fd)
{
	char	*line;

	game->height = 0;
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

void	get_no_texture(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "NO ", 3))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->image_paths[0] = ft_substr(line, 3, ft_strlen(line) - 4);
	free (line);
}

void	get_so_texture(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "SO ", 3))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->image_paths[1] = ft_substr(line, 3, ft_strlen(line) - 4);
	free (line);
}

void	get_we_texture(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "WE ", 3))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->image_paths[2] = ft_substr(line, 3, ft_strlen(line) - 4);
	free (line);
}

void	get_ea_texture(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		game_exit(game, -1);
	}
	if (ft_strncmp(line, "EA ", 3))
	{
		close (fd);
		free (line);
		game_exit(game, -1);
	}
	game->image_paths[3] = ft_substr(line, 3, ft_strlen(line) - 4);
	free (line);
}
