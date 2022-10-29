/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 21:19:43 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/10/29 22:49:32 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Gets the texture and checks if we have double texture keys
*/

int	get_texture(t_game *game, char **line, int num)
{
	if (game->image_paths[num] == NULL)
		game->image_paths[num] = ft_substr(*line, 3, ft_strlen(*line) - 4);
	else
		game->error = -1;
	return (1);
}

/*
** Gets the color and checks if we have double color keys
*/

int	get_rgb(t_game *game, char **line, int match)
{
	if (match == 1 && game->f_color.a == -1)
		game->f_color = encode_rgb(*line, game);
	else if (match == 2 && game->c_color.a == -1)
		game->c_color = encode_rgb(*line, game);
	else
		game->error = -1;
	return (1);
}

/*
** Helper function to parse all .cub keys
*/

int	parse_texture(t_game *game, char **line)
{
	if (!ft_strncmp(*line, "NO ", 3))
		return (get_texture(game, line, 0));
	if (!ft_strncmp(*line, "SO ", 3))
		return (get_texture(game, line, 1));
	if (!ft_strncmp(*line, "WE ", 3))
		return (get_texture(game, line, 2));
	if (!ft_strncmp(*line, "EA ", 3))
		return (get_texture(game, line, 3));
	if (!ft_strncmp(*line, "F ", 2))
		return (get_rgb(game, line, 1));
	if (!ft_strncmp(*line, "C ", 2))
		return (get_rgb(game, line, 2));
	return (0);
}
