/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:27:19 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/04 11:09:27 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_ray_angle(t_ray	*ray, double rayangle)
{
	ray->angle = rayangle;
	if (ray->angle >= PI)
		ray->facing_up = true;
	else
		ray->facing_up = false;
	if (ray->angle <= (PI / 2) || ray->angle >= ((3 * PI) / 2))
		ray->facing_right = true;
	else
		ray->facing_right = false;
}

void	set_texture(t_ray *ray, t_data *data, t_img *texture)
{
	if (is_door(data, ray->intersection.x, ray->intersection.y, 0))
		*texture = data->map_data->txt.door;
	else if (ray->was_hit_vertical)
	{
		if (ray->facing_right)
			*texture = data->map_data->txt.walls[1];
		else
			*texture = data->map_data->txt.walls[3];
	}
	else
	{
		if (ray->facing_up)
			*texture = data->map_data->txt.walls[0];
		else
			*texture = data->map_data->txt.walls[2];
	}
}

bool	is_wall_1(double x, double y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_y = (int)floor((double)y / (double)(TILE_SIZE + EPSILON));
	map_x = (int)floor((double)x / (double)(TILE_SIZE + EPSILON));
	if ((map_y < 0 || map_y >= data->map_data->map.rows) || \
		(map_x < 0 || map_x >= data->map_data->map.cols))
		return (true);
	if (data->map_data->map.map[map_y][map_x] == '1'
		|| data->map_data->map.map[map_y][map_x] == '2')
		return (true);
	else
		return (false);
}

bool	is_wall_2(double x, double y, t_data *data)
{
	int	map_x;
	int	map_y;

	map_y = (int)floor((double)y / (double)TILE_SIZE);
	map_x = (int)floor((double)x / (double)TILE_SIZE);
	if ((map_y < 0 || map_y >= data->map_data->map.rows) || \
		(map_x < 0 || map_x >= data->map_data->map.cols))
		return (true);
	if (data->map_data->map.map[map_y][map_x] == '1')
		return (true);
	else
		return (false);
}

double	get_wall_height(t_data *data, t_ray *ray)
{
	double	corrected_distance;
	double	dist_proj_plane;

	corrected_distance = ray->distance * \
			cos(ray->angle - data->player->rotation_angle);
	dist_proj_plane = ((double)WIDTH / 2) / tan(FOV / 2);
	return (((double)TILE_SIZE / corrected_distance) * dist_proj_plane);
}
