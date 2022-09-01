/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_map_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:36:39 by skorte            #+#    #+#             */
/*   Updated: 2022/04/03 17:07:04 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** Part of t_map struct init. Fills in parameters to start the game.
*/

static void	ft_t_map_set_pos(t_map *map)
{
	map->p_key = 'd';
	map->g_key = 'a';
	map->p_pos = (int)(ft_strchr(map->tiles, 'P') - map->tiles);
	map->p_old = (int)(ft_strchr(map->tiles, 'P') - map->tiles);
	if (ft_strchr(map->tiles, 'G'))
	{
		map->g_pos = (int)(ft_strchr(map->tiles, 'G') - map->tiles);
		map->g_old = (int)(ft_strchr(map->tiles, 'G') - map->tiles);
	}
	else if (GUARD)
		ft_guard_pos_generator(map);
	else
	{
				map->g_pos = 0;
				map->g_old = 0;
	}
	map->exitmode = 0;
	map->redraw = 1;
	map->anim_counter = 0;
	map->steps = 0;
	map->last_guard_move = time(NULL);
}

/*
** Tests if the mapfile contained a valid map
**
** Tests if only allowed characters.
** 'P', 'E', 'C' are mandatory.
** 'P' is allowed once.
** If compiled wuth GUARD=1, G is allowed.
** Tests if surrounded by '1'.
** Tests if all lines have the same length.
*/

static void	ft_t_map_test(t_map *map)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(map->tiles))
	{
		if (!ft_strchr("10PECG\n", map->tiles[i]))
			ft_exit(map, -1);
		if (map->tiles[i] != '1')
			if (i % (map->width + 1) == 0
				|| i % (map->width + 1) == (map->width - 1)
				|| i < map->width
				|| ((i >= (map->width + 1) * (map->height - 1))
					&& i < (map->width + 1) * (map->height) - 1))
				ft_exit(map, -1);
		if (map->tiles[i] == 'G' && !GUARD)
			ft_exit(map, -1);
		if ((map->tiles[i] != '\n' && (i + 1) % (map->width + 1) == 0)
			|| (map->tiles[i] == '\n' && (i + 1) % (map->width + 1) != 0))
			ft_exit(map, -1);
		i++;
	}
	if (ft_strchr(ft_strchr(map->tiles, 'P') + 1, 'P')
		|| !ft_strchr(map->tiles, 'P') || !ft_strchr(map->tiles, 'E')
		|| !ft_strchr(map->tiles, 'C'))
		ft_exit (map, -1);
}

/*
** Opens the map file if the path is correct, returns file descriptor.
** Exits with error if no correct file or file name.
*/

static int	ft_open_ber(char *path)
{
	int		fd;

	if (!ft_strnstr(path, ".ber", ft_strlen(path)))
		ft_exit(NULL, -3);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_exit(NULL, -3);
	return (fd);
}

/*
** Allocates memory for the t_map struct.
** Fills the t_map struct with data from the *.ber file given in 'path'.
** Returns the map.
*/

t_map	*ft_t_map_init(char *path)
{
	t_map	*map;
	int		fd;
	char	*line;
	char	*temp;

	fd = ft_open_ber(path);
	map = malloc(sizeof(t_map));
	line = get_next_line(fd);
	map->width = ft_strlen(line) - 1;
	map->height = 1;
	map->tiles = line;
	line = get_next_line(fd);
	while (line && map->height++)
	{
		temp = ft_strjoin(map->tiles, line);
		free (map->tiles);
		free (line);
		map->tiles = temp;
		line = get_next_line(fd);
	}
	map->mlx = NULL;
	map->mlx_win = NULL;
	ft_t_map_test(map);
	ft_t_map_set_pos(map);
	return (map);
}
