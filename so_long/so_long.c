/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:34:57 by skorte            #+#    #+#             */
/*   Updated: 2022/04/01 10:50:24 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char	**argv)
{
	t_map	*map;

	map = NULL;
	srand(time(0));
	if (argc != 2)
		ft_exit(NULL, -3);
	map = ft_t_map_init(argv[1]);
	ft_mlx_init(map);
	ft_exit(map, 65307);
	return (0);
}
