/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 23:42:09 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/10/28 15:09:42 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Check if all textures and colors are defined
*/

void	check_options(t_game *game)
{
	if (!game->image_paths[0] || !game->image_paths[1]
		|| !game->image_paths[2] || !game->image_paths[3])
		game_exit(game, -1);
	if (game->c_color.a == -1 || game->f_color.a == -1)
		game_exit(game, -5);
}

/*
** Parser for textures and colors
*/

int	parse_texture(t_game *game, char **line)
{
	if (!ft_strncmp(*line, "NO ", 3))
	{
		if (game->image_paths[0] == NULL)
			game->image_paths[0] = ft_substr(*line, 3, ft_strlen(*line) - 4);
		return (1);
	}
	if (!ft_strncmp(*line, "SO ", 3))
	{
		if (game->image_paths[1] == NULL)
			game->image_paths[1] = ft_substr(*line, 3, ft_strlen(*line) - 4);
		return (1);
	}
	else if (!ft_strncmp(*line, "WE ", 3))
	{
		if (game->image_paths[2] == NULL)
			game->image_paths[2] = ft_substr(*line, 3, ft_strlen(*line) - 4);
		return (1);
	}
	else if (!ft_strncmp(*line, "EA ", 3))
	{
		if (game->image_paths[3] == NULL)
			game->image_paths[3] = ft_substr(*line, 3, ft_strlen(*line) - 4);
		return (1);
	}
	return (0);
}

void	parse_option(int fd, t_game *game, int *i, char **line)
{
	*line = get_next_line(fd);
	if (!*line)
	{
		free(line);
		game_exit(game, -1);
	}
	printf("%s", *line);
	if (parse_texture(game, line))
		;
	else if (!ft_strncmp(*line, "F ", 2))
		game->f_color = encode_rgb(*line);
	else if (!ft_strncmp(*line, "C ", 2))
		game->c_color = encode_rgb(*line);
	else if (*line[0] != '\n')
		return ;
	free(*line);
	(*i)++;
	parse_option(fd, game, i, line);
}

void	mapstrcpy(t_game *game, int a)
{
	int		i;
	char	*str;

	i = game->width;
	str = ft_calloc(sizeof(char), i + 1);
	while (i > 0)
	{
		str[i - 1] = ' ';
		i--;
	}
	i = 0;
	while (str[i] && game->map[a][i])
	{
		if (game->map[a][i] != '\n')
			str[i] = game->map[a][i];
		i++;
	}
	free(game->map[a]);
	game->map[a] = str;
}

void	parse_map(int fd, t_game *game, int i)
{
	skip_lines(game, fd, i);
	i = 0;
	while (i < game->height)
	{
		game->map[i] = get_next_line(fd);
		mapstrcpy(game, i);
		printf("%s-\n", game->map[i]);
		i++;
	}
	map_test(game);
	printf("Map ok.\n");
}
