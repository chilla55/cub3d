/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:39 by skorte            #+#    #+#             */
/*   Updated: 2022/10/26 10:48:47 by skorte           ###   ########.fr       */
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
	game->c_color = getcolor(-1, -1, -1, -1);
	game->f_color = getcolor(-1, -1, -1, -1);
}

void	set_player_pos(t_game *game, int x, int y)
{
	char	c;

	c = game->map[x][y];
	if (!ft_strchr("NSWE", c))
		return ;
	else if (c == 'W')
		game->angle = 270.0;
	else if (c == 'N')
		game->angle = 0.0;
	else if (c == 'E')
		game->angle = 90.0;
	else if (c == 'S')
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
	int		fd;
	int		i;
	int		a;
	char	*line;

	a = 0;
	fd = open_cub(game, path);
	parse_option(fd, game, &a, &line);
	printf("%d", a);
	i = 0;
	while (i < 4)
	{
		printf("%s\n", game->image_paths[i]);
		i++;
	}
	get_size(game, fd, line);
	close (fd);
	if (game->c_color.a == -1 || game->f_color.a == -1)
		game_exit(game, -5);
	printf("%d,%d,%d,%d\n", game->f_color.a, game->f_color.r,
		game->f_color.g, game->f_color.b);
	printf("%d,%d,%d,%d\n", game->c_color.a, game->c_color.r,
		game->c_color.g, game->c_color.b);
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
	game->scale = X_RES / 5.0 / game->width;
	if (Y_RES / 5.0 / game->height < game->scale)
		game->scale = Y_RES / 5.0 / game->height;
	return (game);
}
