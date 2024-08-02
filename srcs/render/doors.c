/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 10:23:36 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/02 10:28:31 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_door(t_data *data, double x, double y, int skip)
{
	int	map_x;
	int	map_y;

	map_y = (int)floor((double)y / (double)TILE_SIZE);
	map_x = (int)floor((double)x / (double)TILE_SIZE);
	if ((map_y < 0 || map_y >= data->map_data->map.rows) || \
		(map_x < 0 || map_x >= data->map_data->map.cols))
		return (true);
	if (data->map_data->map.map[map_y][map_x] == '2')
		return (true);
	else if (!skip && data->map_data->map.map[map_y][map_x] == '3')
		return (true);
	else
		return (false);
}

void	toggle_door(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_y = (int)floor((double)y / (double)TILE_SIZE);
	map_x = (int)floor((double)x / (double)TILE_SIZE);
	if ((map_y < 0 || map_y >= data->map_data->map.rows) || \
		(map_x < 0 || map_x >= data->map_data->map.cols))
	{
		printf(RED"invalid door\n"RESET);
		return ;
	}
	if (data->map_data->map.map[map_y][map_x] == '2')
	{
		play_sound_bg(OPEN_DOOR);
		data->map_data->map.map[map_y][map_x] = '3';
	}
	else if (data->map_data->map.map[map_y][map_x] == '3')
	{
		play_sound_bg(CLOSE_DOOR);
		data->map_data->map.map[map_y][map_x] = '2';
	}
	else
		return (printf(RED"NOT a door\n"RESET), (void)0);
}

void	handle_doors(t_data *data)
{
	t_ray		ray;
	t_player	*player;

	player = data->player;
	ray.column = -1;
	cast_ray(data, &ray, normalize_angle(player->rotationAngle), 0);
	if (is_door(data, ray.intersection.x, ray.intersection.y, 0) \
		&& ray.distance < (double)(TILE_SIZE * 2))
		toggle_door(data, ray.intersection.x, ray.intersection.y);
}
