/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrotzsc <agrotzsc@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:33:03 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/09/19 12:53:19 by agrotzsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	checkvalid(int *i)
{
	if ((i[0] <= 255 && i[0] >= 0) || (i[1] <= 255 && i[1] >= 0)
		|| (i[2] <= 255 && i[2] >= 0))
		return (1);
	return (0);
}

/*
** Parser for textures and colors
*/

int	encode_rgb(char *str)
{
	int		color;
	int		tempi[3];
	char	**temp;

	str = ft_substr(str, 2, ft_strlen(str) - 3);
	temp = ft_split(str, ',');
	tempi[0] = ft_atoi(temp[0]);
	tempi[1] = ft_atoi(temp[1]);
	tempi[2] = ft_atoi(temp[2]);
	free(str);
	free_split(temp);
	if (!checkvalid(tempi))
		return (0);
	color = (tempi[0] << 16 | tempi[1] << 8 | tempi[2]);
	return (color);
}
