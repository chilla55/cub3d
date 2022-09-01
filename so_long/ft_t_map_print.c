/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_map_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:40:33 by skorte            #+#    #+#             */
/*   Updated: 2022/04/06 08:53:19 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*
** ft_clear clears the console output, so a new frame can be rendered there.
*/

static void	ft_clear(void)
{
	int	i;

	i = 0;
	i += write(1, &"\e[1;1H\e[2J", 10);
}

/*
** ft_t_map_print writes the content of the map to the console.
*/

void	ft_t_map_print(t_map *map)
{
	char	*step_str;
	char	*tiles_ptr;
	int		i;

	ft_clear();
	tiles_ptr = map->tiles;
	while (tiles_ptr[0])
	{
		if (tiles_ptr[0] == '0')
			i = write(1, &" ", 1);
		else
			i = write(1, tiles_ptr, 1);
		tiles_ptr++;
	}
	tiles_ptr--;
	if (tiles_ptr[0] != '\n')
		i = write(1, &"\n", 1);
	step_str = ft_itoa(map->steps);
	i = write(1, "You made ", 9);
	i = write(1, step_str, ft_strlen(step_str));
		i = write(1, " move", 5);
	if (map->steps != 1)
		i = write(1, "s", 1);
	free (step_str);
	i += write(1, &".\n", 2);
}
