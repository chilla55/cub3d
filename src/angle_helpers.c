/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:20:27 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 19:34:58 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Conversion between angles in degree and radian measure.
*/

double	cal_radian(double degree)
{
	return (degree / 180 * PI);
}

double	cal_degree(double radian)
{
	return (radian * 180 / PI);
}
