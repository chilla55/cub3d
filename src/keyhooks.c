/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:21:52 by skorte            #+#    #+#             */
/*   Updated: 2022/09/15 19:18:33 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_pos(t_game *game, int key);
static int	rot_pos(t_game *game, int key);

/*
** key_hook defines the action that happens upon key-down events.
** The escape key (key code 65307) triggers the program to exit.
** In case a change in position (either x_pos / y_pos or angle)
** occured, the game-loop will be started to recalculate and
** redraw the image.
*/

int	key_hook(int key, void *game_void)
{
	t_game	*game;

	game = ((t_game *)game_void);
	if (move_pos(game, key))
		game_loop(game);
	else if (rot_pos(game, key))
		game_loop(game);
	else if (key == 65307)
		game_exit (game, 65307);
	return (0);
}

/*
** Changes the camera position according to the keys 'wasd'.
** Returns 1 if the position is changed.
** Returns 0 if no corresponding key was detected
** or if the movement would end inside a wall.
*/

static int	move_pos(t_game *game, int key)
{
	double	step_size;
	double	direction;
	double	new_x_pos;
	double	new_y_pos;

	step_size = 0.1;
	if (key == 'w')
		direction = 270;
	else if (key == 'a')
		direction = 0;
	else if (key == 's')
		direction = 90;
	else if (key == 'd')
		direction = 180;
	else
		return (0);
	direction += game->angle;
	new_x_pos = game->x_pos + step_size * cos(cal_radian(direction));
	new_y_pos = game->y_pos + step_size * -sin(cal_radian(direction));
	if (game->map[(int)ceil(new_x_pos)][(int)ceil(new_y_pos)] != '1')
	{
		game->x_pos = new_x_pos;
		game->y_pos = new_y_pos;
		return (1);
	}
	return (0);
}

/*
** Changes the camera angle according to the keypress.
** Returns 1 if the angle is changed.
** Returns 0 if no corresponding key was detected.
*/

static int	rot_pos(t_game *game, int key)
{
	double	step_size;

	step_size = 5;
	if (key == 65363)
		game->angle += step_size;
	else if (key == 65361)
		game->angle -= step_size;
	else
		return (0);
	return (1);
}
