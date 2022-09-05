/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:59:31 by agrotzsc          #+#    #+#             */
/*   Updated: 2022/09/05 14:14:04 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	printf("CUB3D\n");
	game = NULL;
	if (argc != 2)
		return (-1);
	game = game_init(argv[1]);
	raycaster_init(game);
	game_mlx_init(game);
	game_exit(game, 0);
	return (0);
}
