/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:15:08 by skorte            #+#    #+#             */
/*   Updated: 2022/10/13 12:21:41 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(t_buff *buffer, t_color color, int x, int y)
{
	int	pixel;

	pixel = (y * buffer->line_bytes) + (x * 4);
	if (buffer->endian == 1)
	{
		buffer->buffer[pixel + 0] = color.a;
		buffer->buffer[pixel + 1] = color.r;
		buffer->buffer[pixel + 2] = color.g;
		buffer->buffer[pixel + 3] = color.b;
	}
	else
	{
		buffer->buffer[pixel + 3] = color.a;
		buffer->buffer[pixel + 2] = color.r;
		buffer->buffer[pixel + 1] = color.g;
		buffer->buffer[pixel + 0] = color.b;
	}
	return ;
}

t_color	extract_pixel(t_buff *buffer, int x, int y)
{
	int		pixel;
	t_color	color;

	pixel = (y * buffer->line_bytes) + (x * 4);
	if (buffer->endian == 1)
	{
		color.a = buffer->buffer[pixel + 0];
		color.r = buffer->buffer[pixel + 1];
		color.g = buffer->buffer[pixel + 2];
		color.b = buffer->buffer[pixel + 3];
	}
	else
	{
		color.a = buffer->buffer[pixel + 3];
		color.r = buffer->buffer[pixel + 2];
		color.g = buffer->buffer[pixel + 1];
		color.b = buffer->buffer[pixel + 0];
	}
	return (color);
}
