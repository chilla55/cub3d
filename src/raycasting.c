/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 23:53:11 by skorte            #+#    #+#             */
/*   Updated: 2022/09/02 00:00:33 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	X_RES rays, equally??? spaced between angle-45 to angle+45 - No, not equally...
	each needs distance to wall, type of wall face (NSWE),
	and point on wall (between 0 and 1 to extract from texture)
*/

void	raycaster_init(t_game *game)
{
	(void)game;
}