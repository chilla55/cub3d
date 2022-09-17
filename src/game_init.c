/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:39 by skorte            #+#    #+#             */
/*   Updated: 2022/09/17 23:06:59 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	null_init(t_game *game)
{
	int	i;

	game->map = NULL;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->frame_buffer = NULL;
	game->buffer = NULL;
	i = 0;
	while (i < 4)
	{
		game->image_paths[i] = NULL;
		game->mlx_images[i] = NULL;
		game->textures[i] = NULL;
		i++;
	}
	i = 0;
	while (i < X_RES)
	{
		game->rays[i] = NULL;
		i++;
	}
}

void	set_player_pos(t_game *game, int x, int y)
{
	char	c;

	c = game->map[x][y];
	if (!ft_strchr("NSWE", c))
		return ;
	else if (c == 'N')
		game->angle = 270.0;
	else if (c == 'E')
		game->angle = 0.0;
	else if (c == 'S')
		game->angle = 90.0;
	else if (c == 'W')
		game->angle = 180.0;
	game->x_pos = (double)y + 0.5;
	game->y_pos = (double)x + 0.5;
}

/*
** Returns a file descriptor for the cub file in path.
** Exits the program if no file could be opened.
*/

int	open_cub(t_game *game, char *path)
{
	int		fd;

	if (!ft_strnstr(path, ".cub", ft_strlen(path)))
		game_exit(game, -3);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		game_exit(game, -3);
	return (fd);
}

/*
** Reads parameter from the cub file into the game struct.
*/

int	get_params(t_game *game, char *path)
{
	int	fd;
	int	i;
	int	a;

	a = 0;
	fd = open_cub(game, path);
	parse_option(fd, game, &a);
	printf("%d", a);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", game->image_paths[i]);
		i++;
	}
	printf("%s\n", game->f_color);
	printf("%s\n", game->c_color);
	get_size(game, fd);
	close (fd);
	return (a);
}

t_game	*game_init(char *path)
{
	t_game	*game;
	int		fd;
	int		i;

	game = malloc(sizeof(t_game));
	null_init(game);
	i = get_params(game, path);
	game->map = malloc(game->height * sizeof(char *));
	fd = open_cub(game, path);
	parse_map(fd, game, i);
	printf("Player position: %f, %f, angle %f\n",
		game->x_pos, game->y_pos, game->angle);
	return (game);
}
