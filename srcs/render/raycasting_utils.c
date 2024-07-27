/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:27:19 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/27 15:15:40 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_ray_angle(t_ray	*ray)
{
	if (ray->angle >= PI)
		ray->facingUp = true;
	else
		ray->facingUp = false;
	if (ray->angle <= (PI / 2) || ray->angle >= ((3 * PI) / 2))
		ray->facingRight = true;
	else
		ray->facingRight = false;
}

void	set_texture(t_ray ray, t_data *data, t_img *texture)
{
	if (ray.wasHitVertical)
	{
		if (ray.facingRight)
		{
			// printf("\t=====> EA\n");
			*texture = data->map_data->ea_texture_img;
		}
		else
		{
			// printf("\t=====> WE\n");
			*texture = data->map_data->we_texture_img;
		}
	}
	else
	{
		if (ray.facingUp)
		{
			// printf("\t=====> NO\n");
			*texture = data->map_data->no_texture_img;
		}
		else
		{
			// printf("\t=====> SO\n");
			*texture = data->map_data->so_texture_img;
		}
	}
}

bool is_wall_1(double x, double y, t_data *data)
{
	int	mapX, mapY;

	mapY = (int)floor((double)y / (double)(TILE_SIZE + EPSILON));
	mapX = (int)floor((double)x / (double)(TILE_SIZE + EPSILON));
	if ((mapY < 0 || mapY >= data->map_data->map.rows) || (mapX < 0 || mapX >= data->map_data->map.cols))
	{
		printf("========> EDGE\n");
		return (true);
	}
	if (data->map_data->map.map[mapY][mapX] == '1')
		return (true);
	else
		return (false);
}

bool is_wall_2(double x, double y, t_data *data)
{
	int	mapX, mapY;

	mapY = (int)floor((double)y / (double)TILE_SIZE);
	mapX = (int)floor((double)x / (double)TILE_SIZE);
	if ((mapY < 0 || mapY >= data->map_data->map.rows) || (mapX < 0 || mapX >= data->map_data->map.cols))
	{
		printf("========> EDGE\n");
		return (true);
	}
	if (data->map_data->map.map[mapY][mapX] == '1')
		return (true);
	else
		return (false);
}