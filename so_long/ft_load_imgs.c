/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_imgs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 10:39:47 by skorte            #+#    #+#             */
/*   Updated: 2022/04/03 16:46:03 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_load_imgs_2(t_map *map, int tls)
{
	map->r[0] = mlx_xpm_file_to_image(map->mlx, "./img/100.xpm", &tls, &tls);
	map->r[1] = mlx_xpm_file_to_image(map->mlx, "./img/101.xpm", &tls, &tls);
	map->r[2] = mlx_xpm_file_to_image(map->mlx, "./img/102.xpm", &tls, &tls);
	map->r[3] = mlx_xpm_file_to_image(map->mlx, "./img/103.xpm", &tls, &tls);
	map->r[4] = mlx_xpm_file_to_image(map->mlx, "./img/104.xpm", &tls, &tls);
	map->e[0] = mlx_xpm_file_to_image(map->mlx, "./img/E.xpm", &tls, &tls);
	map->o[0] = mlx_xpm_file_to_image(map->mlx, "./img/000.xpm", &tls, &tls);
	map->o[1] = mlx_xpm_file_to_image(map->mlx, "./img/001.xpm", &tls, &tls);
	map->o[2] = mlx_xpm_file_to_image(map->mlx, "./img/002.xpm", &tls, &tls);
	map->o[3] = mlx_xpm_file_to_image(map->mlx, "./img/003.xpm", &tls, &tls);
	map->o[4] = mlx_xpm_file_to_image(map->mlx, "./img/010.xpm", &tls, &tls);
	map->o[5] = mlx_xpm_file_to_image(map->mlx, "./img/011.xpm", &tls, &tls);
	map->o[6] = mlx_xpm_file_to_image(map->mlx, "./img/012.xpm", &tls, &tls);
	map->o[7] = mlx_xpm_file_to_image(map->mlx, "./img/013.xpm", &tls, &tls);
	map->o[8] = mlx_xpm_file_to_image(map->mlx, "./img/020.xpm", &tls, &tls);
	map->o[9] = mlx_xpm_file_to_image(map->mlx, "./img/021.xpm", &tls, &tls);
	map->o[10] = mlx_xpm_file_to_image(map->mlx, "./img/022.xpm", &tls, &tls);
	map->o[11] = mlx_xpm_file_to_image(map->mlx, "./img/023.xpm", &tls, &tls);
	map->o[12] = mlx_xpm_file_to_image(map->mlx, "./img/030.xpm", &tls, &tls);
	map->o[13] = mlx_xpm_file_to_image(map->mlx, "./img/031.xpm", &tls, &tls);
	map->o[14] = mlx_xpm_file_to_image(map->mlx, "./img/032.xpm", &tls, &tls);
	map->o[15] = mlx_xpm_file_to_image(map->mlx, "./img/033.xpm", &tls, &tls);
}

void	ft_load_imgs(t_map *map, int tls)
{
	map->p[0] = mlx_xpm_file_to_image(map->mlx, "./img/P01.xpm", &tls, &tls);
	map->p[1] = mlx_xpm_file_to_image(map->mlx, "./img/P02.xpm", &tls, &tls);
	map->p[2] = mlx_xpm_file_to_image(map->mlx, "./img/P03.xpm", &tls, &tls);
	map->p[3] = mlx_xpm_file_to_image(map->mlx, "./img/P04.xpm", &tls, &tls);
	map->g[0] = mlx_xpm_file_to_image(map->mlx, "./img/G01.xpm", &tls, &tls);
	map->g[1] = mlx_xpm_file_to_image(map->mlx, "./img/G02.xpm", &tls, &tls);
	map->g[2] = mlx_xpm_file_to_image(map->mlx, "./img/G03.xpm", &tls, &tls);
	map->g[3] = mlx_xpm_file_to_image(map->mlx, "./img/G04.xpm", &tls, &tls);
	map->w[0] = mlx_xpm_file_to_image(map->mlx, "./img/W01.xpm", &tls, &tls);
	map->w[1] = mlx_xpm_file_to_image(map->mlx, "./img/W02.xpm", &tls, &tls);
	map->w[2] = mlx_xpm_file_to_image(map->mlx, "./img/W03.xpm", &tls, &tls);
	map->w[3] = mlx_xpm_file_to_image(map->mlx, "./img/W04.xpm", &tls, &tls);
	map->c[0] = mlx_xpm_file_to_image(map->mlx, "./img/C00.xpm", &tls, &tls);
	map->c[1] = mlx_xpm_file_to_image(map->mlx, "./img/C01.xpm", &tls, &tls);
	map->c[2] = mlx_xpm_file_to_image(map->mlx, "./img/C02.xpm", &tls, &tls);
	map->c[3] = mlx_xpm_file_to_image(map->mlx, "./img/C03.xpm", &tls, &tls);
	map->x[0] = mlx_xpm_file_to_image(map->mlx, "./img/X00.xpm", &tls, &tls);
	map->x[1] = mlx_xpm_file_to_image(map->mlx, "./img/X01.xpm", &tls, &tls);
	map->x[2] = mlx_xpm_file_to_image(map->mlx, "./img/X02.xpm", &tls, &tls);
	map->x[3] = mlx_xpm_file_to_image(map->mlx, "./img/X03.xpm", &tls, &tls);
	map->x[4] = mlx_xpm_file_to_image(map->mlx, "./img/X04.xpm", &tls, &tls);
	map->x[5] = mlx_xpm_file_to_image(map->mlx, "./img/X05.xpm", &tls, &tls);
	map->x[6] = mlx_xpm_file_to_image(map->mlx, "./img/X06.xpm", &tls, &tls);
	ft_load_imgs_2(map, tls);
}

void	ft_free_imgs(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		mlx_destroy_image(map->mlx, map->p[i]);
		mlx_destroy_image(map->mlx, map->g[i]);
		mlx_destroy_image(map->mlx, map->w[i]);
		mlx_destroy_image(map->mlx, map->c[i]);
	}
	i = -1;
	while (++i < 7)
		mlx_destroy_image(map->mlx, map->x[i]);
	i = -1;
	while (++i < 16)
		mlx_destroy_image(map->mlx, map->o[i]);
	i = -1;
	while (++i < 5)
		mlx_destroy_image(map->mlx, map->r[i]);
	mlx_destroy_image(map->mlx, map->e[0]);
}
