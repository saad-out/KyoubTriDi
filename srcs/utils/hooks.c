/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:19:43 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/05 10:45:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	mouse_move(int x, int y, t_data *data)
{
	static int	old_x = 0;
	int			diff_x;

	y = 0;
	diff_x = x - old_x;
	old_x = x - y;
	data->player->rotation_angle += diff_x * 0.005;
	return (0);
}

void	player_movement_hooks(int keycode, t_data *data)
{
	if (keycode == UP_ARROW || keycode == W)
		data->player->walk_direction = 1;
	else if (keycode == DOWN_ARROW || keycode == S)
		data->player->walk_direction = -1;
	else if (keycode == LEFT_ARROW)
		data->player->turn_direction = -1;
	else if (keycode == RIGHT_ARROW)
		data->player->turn_direction = 1;
	else if (keycode == A)
	{
		data->player->walk_direction = -1;
		data->player->hor_move = PI2;
	}
	else if (keycode == D)
	{
		data->player->walk_direction = 1;
		data->player->hor_move = PI2;
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
		data->player->walk_direction = 0;
	}
	else if (keycode == LEFT_ARROW || keycode == RIGHT_ARROW)
	{
		data->player->turn_direction = 0;
		data->player->hor_move = 0;
	}
	else if (keycode == A || keycode == D)
	{
		data->player->walk_direction = 0;
		data->player->hor_move = 0;
	}
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_realse, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 17, 0, close_window, data);
}
