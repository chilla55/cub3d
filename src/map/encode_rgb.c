/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:33:03 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/10/29 22:47:23 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	checkvalid(int *i, t_game *game)
{
	if ((i[0] <= 255 && i[0] >= 0) && (i[1] <= 255 && i[1] >= 0)
		&& (i[2] <= 255 && i[2] >= 0))
		return (1);
	game->error = -2;
	return (0);
}

t_color	getcolor(int a, int r, int g, int b)
{
	t_color	c;

	c.a = a;
	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

/*
** Parser for textures and colors
*/

t_color	encode_rgb(char *str, t_game *game)
{
	int		tempi[3];
	char	**temp;
	char	*temps;

	temps = ft_substr(str, 2, ft_strlen(str) - 2);
	temp = ft_split(temps, ',');
	tempi[0] = -1;
	tempi[1] = -1;
	tempi[2] = -1;
	if (temp[0] != NULL)
	{
		tempi[0] = ft_atoi(temp[0]);
		if (temp[1] != NULL)
		{	
			tempi[1] = ft_atoi(temp[1]);
			if (temp[2] != NULL)
				tempi[2] = ft_atoi(temp[2]);
		}
	}
	free(temps);
	free_split(temp);
	if (!checkvalid(tempi, game))
		return (getcolor(-1, -1, -1, -1));
	return (getcolor(0, tempi[0], tempi[1], tempi[2]));
}
