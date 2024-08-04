/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:19:43 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 10:13:43 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	static int	old_x = 0;
	static int	old_y = 0;
	int			diff_x;
	int			diff_y;

	diff_x = x - old_x;
	diff_y = y - old_y;
	old_x = x;
	old_y = y;
	data->player->rotationAngle += diff_x * 0.005;
	return (0);
}

void	player_movement_hooks(int keycode, t_data *data)
{
	if (keycode == UP_ARROW || keycode == W)
		data->player->walkDirection = 1;
	else if (keycode == DOWN_ARROW || keycode == S)
		data->player->walkDirection = -1;
	else if (keycode == LEFT_ARROW)
		data->player->turnDirection = -1;
	else if (keycode == RIGHT_ARROW)
		data->player->turnDirection = 1;
	else if (keycode == A)
	{
		data->player->walkDirection = -1;
		data->player->horMove = PI_2;
	}
	else if (keycode == D)
	{
		data->player->walkDirection = 1;
		data->player->horMove = PI_2;
	}
	else if (keycode == T)
		handle_doors(data);
}

int	key_press(int keycode, t_data *data)
{
	player_movement_hooks(keycode, data);
	if (keycode == ESC)
	{
		set_exit_flag(data);
		running_threads(STOP, 0);
		free_all_mem(data);
		ao_shutdown();
		exit(0);
	}
	return (0);
}

int	key_realse(int keycode, t_data *data)
{
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

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_realse, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
}
