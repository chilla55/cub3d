/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:33:03 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/10/15 19:13:40 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	checkvalid(int *i)
{
	if ((i[0] <= 255 && i[0] >= 0) && (i[1] <= 255 && i[1] >= 0)
		&& (i[2] <= 255 && i[2] >= 0))
		return (1);
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

t_color	encode_rgb(char *str)
{
	t_color	color;
	int		tempi[3];
	char	**temp;
	char	*temps;

	temps = ft_substr(str, 2, ft_strlen(str) - 2);
	temp = ft_split(temps, ',');
	tempi[0] = ft_atoi(temp[0]);
	tempi[1] = ft_atoi(temp[1]);
	tempi[2] = ft_atoi(temp[2]);
	free(temps);
	free_split(temp);
	if (!checkvalid(tempi))
		return (getcolor(-1, -1, -1, -1));
	color.a = 0;
	color.r = tempi[0];
	color.g = tempi[1];
	color.b = tempi[2];
	return (color);
}
