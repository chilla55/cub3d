/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:39 by skorte            #+#    #+#             */
/*   Updated: 2022/09/01 23:22:46 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Tests if the cubfile contains a valid map.
** Only allowed characters?
** Exactly one player position 'NWES' is mandatory.
** Tests if surrounded by '1'.
*/

void	null_init(t_game *game)
{
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	game->f_color = NULL;
	game->c_color = NULL;
}

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
			if (!ft_strchr("10NWSE \n", game->map[i][j]))
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
			j++;
		}
		i++;
	}
	if (p != 1)
		game_exit(game, -1);
	printf("Map ok.\n");
}

static int	open_cub(char *path)
{
	int		fd;

	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		game_exit(NULL, -3);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		game_exit(NULL, -3);
	return (fd);
}

void	get_size(t_game *game, char *path)
{
	int		fd;
	char	*line;

	fd = open_cub(path);
	game->height = -8;
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
	close (fd);
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
	game->no_path = ft_substr(line, 3, ft_strlen(line) - 4);
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
	game->so_path = ft_substr(line, 3, ft_strlen(line) - 4);
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
	game->we_path = ft_substr(line, 3, ft_strlen(line) - 4);
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
	game->ea_path = ft_substr(line, 3, ft_strlen(line) - 4);
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

void	get_params(t_game *game, char *path)
{
	int		fd;

	fd = open_cub(path);
	get_no_texture(game, fd);
	printf("%s\n", game->no_path);
	get_so_texture(game, fd);
	printf("%s\n", game->so_path);
	get_we_texture(game, fd);
	printf("%s\n", game->we_path);
	get_ea_texture(game, fd);
	printf("%s\n", game->ea_path);
	skip_empty_line(game, fd);
	get_f_color(game, fd);
	printf("%s\n", game->f_color);
	get_c_color(game, fd);
	printf("%s\n", game->c_color);
	skip_empty_line(game, fd);
	close (fd);
	return ;
}

t_game	*game_init(char *path)
{
	t_game	*game;
	int		fd;
	int		i;

	game = malloc(sizeof(t_game));
	null_init(game);
	get_params(game, path);
	get_size(game, path);
	game->map = malloc(game->height * sizeof(char *));
	fd = open_cub(path);
	i = 0;
	skip_lines(game, fd);
	while (i < game->height)
	{
		game->map[i] = get_next_line(fd);
		printf("%s", game->map[i]);
		i++;
	}
	printf("\n");
	map_test(game);
	game->mlx = NULL;
	game->mlx_win = NULL;
	return (game);
}
