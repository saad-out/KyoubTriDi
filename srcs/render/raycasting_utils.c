/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:27:19 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/31 12:25:15 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_ray_angle(t_ray	*ray, double rayangle)
{
	ray->angle = rayangle;
	if (ray->angle >= PI)
		ray->facingUp = true;
	else
		ray->facingUp = false;
	if (ray->angle <= (PI / 2) || ray->angle >= ((3 * PI) / 2))
		ray->facingRight = true;
	else
		ray->facingRight = false;
}

void	set_texture(t_ray *ray, t_data *data, t_img *texture)
{
	if (is_door(data, ray->intersection.x, ray->intersection.y, 0))
		*texture = data->map_data->door_img;
	else if (ray->wasHitVertical)
	{
		if (ray->facingRight)
			*texture = data->map_data->ea_texture_img;
		else
			*texture = data->map_data->we_texture_img;
	}
	else
	{
		if (ray->facingUp)
			*texture = data->map_data->no_texture_img;
		else
			*texture = data->map_data->so_texture_img;
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
			cos(ray->angle - data->player->rotationAngle);
	dist_proj_plane = ((double)WIDTH / 2) / tan(FOV / 2);
	return (((double)TILE_SIZE / corrected_distance) * dist_proj_plane);
}
