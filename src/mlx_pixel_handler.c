/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:15:08 by skorte            #+#    #+#             */
/*   Updated: 2022/09/19 17:23:17 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_buff *buffer, int color, int x, int y)
{
	int	pixel;

	pixel = (y * buffer->line_bytes) + (x * 4);
	if (buffer->endian == 1)
	{
		buffer->buffer[pixel + 0] = (color >> 24);
		buffer->buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer->buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer->buffer[pixel + 3] = (color) & 0xFF;
	}
	else
	{
		buffer->buffer[pixel + 0] = (color) & 0xFF;
		buffer->buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer->buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer->buffer[pixel + 3] = (color >> 24);
	}
	return ;
}

int	extract_pixel(t_buff *buffer, int x, int y)
{
	int	pixel;
	int	color;

	pixel = (y * buffer->line_bytes) + (x * 4);
	if (buffer->endian == 1)
	{
		color = buffer->buffer[pixel + 0];
		color += buffer->buffer[pixel + 1] >> 8;
		color += buffer->buffer[pixel + 2] >> 16;
		color += buffer->buffer[pixel + 3] >> 24;
	}
	else
	{
		color = buffer->buffer[pixel + 0];
		color += buffer->buffer[pixel + 1] >> 8;
		color += buffer->buffer[pixel + 2] >> 16;
		color += buffer->buffer[pixel + 3] >> 24;
	}
	return (color);
}
