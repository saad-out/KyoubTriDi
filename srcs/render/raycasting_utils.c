/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 05:27:19 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/23 06:41:19 by soutchak         ###   ########.fr       */
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