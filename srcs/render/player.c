/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:18:16 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/04 11:01:16 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	cannot_move(double x, double y, t_data *data)
{
	return (
		is_wall_1(x - PLAYER_SIZE, y - PLAYER_SIZE, data) \
		|| is_wall_1(x + PLAYER_SIZE, y - PLAYER_SIZE, data) \
		|| is_wall_1(x - PLAYER_SIZE, y + PLAYER_SIZE, data) \
		|| is_wall_1(x + PLAYER_SIZE, y + PLAYER_SIZE, data)
	);
}

void	handle_collision(double *nx, double *ny, t_point p, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (!cannot_move(player->x + p.x, player->y + p.y, data))
	{
		*nx = player->x + p.x;
		*ny = player->y + p.y;
	}
	else if (!cannot_move(player->x + p.x, player->y, data))
	{
		*nx = player->x + floor(p.x / 2);
		*ny = player->y;
	}
	else if (!cannot_move(player->x, player->y + p.y, data))
	{
		*nx = player->x;
		*ny = player->y + floor(p.y / 2);
	}
	else
	{
		*nx = player->x;
		*ny = player->y;
	}
}

void	move_player(t_data *data)
{
	t_player	*player;
	double		movestep;
	double		next_y;
	double		next_x;
	t_point		step;

	player = data->player;
	movestep = player->walk_direction * player->walk_speed;
	player->rotation_angle += player->turn_direction * player->turen_speed;
	step.x = cos(player->rotation_angle + player->hor_move) * movestep;
	step.y = sin(data->player->rotation_angle + player->hor_move) * movestep;
	handle_collision(&next_x, &next_y, step, data);
	data->player->x = next_x;
	data->player->y = next_y;
}
