/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:19:43 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/31 10:27:30 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	static int	old_x = 0;
	static int	old_y = 0;
	int			diff_x;
	int			diff_y;

	// printf("Mouse moved\n");
	// printf("x: %d, y: %d\n", x, y);
	diff_x = x - old_x;
	diff_y = y - old_y;
	old_x = x;
	old_y = y;
	data->player->rotationAngle += diff_x * 0.005;
	data->player->horMove += diff_y * 0.005;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	int	movestep;

	// printf(GREEN"keypress\n"RESET);
	float next_y, next_x;
	if (keycode == UP_ARROW || keycode == W)
	{
		data->player->walkDirection = 1;
	}
	else if (keycode == DOWN_ARROW || keycode == S)
	{
		data->player->walkDirection = -1;
	}
	else if (keycode == LEFT_ARROW)
	{
		data->player->turnDirection = -1;
	}
	else if (keycode == RIGHT_ARROW)
	{
		data->player->turnDirection = 1;
	}
	else if (keycode == A)
	{
		data->player->walkDirection = -1; // Move left
		data->player->horMove = PI_2;
	}
	else if (keycode == D)
	{
		data->player->walkDirection = 1; // Move right
		data->player->horMove = PI_2;
	}
	else if (keycode == ESC)
	{
		// free all the allocated memory
		exit(0);
	}
	// move_player(data);
	return (0);
}

int	key_realse(int keycode, t_data *data)
{
	// printf(RED"keyprelease\n"RESET);
	if (keycode == UP_ARROW || keycode == DOWN_ARROW || keycode == W
		|| keycode == S)
	{
		data->player->walkDirection = 0;
	}
	else if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
	{
		data->player->turnDirection = 0;
		data->player->horMove = 0;
	}
	else if (keycode == A || keycode == D)
	{
		data->player->walkDirection = 0;
		data->player->horMove = 0;
	}
	return (0);
}
