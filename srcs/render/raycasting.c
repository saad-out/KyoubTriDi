/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:18:50 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/28 14:37:57 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cast_ray(t_data *data, t_player *player, t_ray *ray, double rayangle)
{
	t_point	hor_inter;
	t_point	ver_inter;
	t_point	min;
	t_point	tmp;

	set_ray_angle(ray, rayangle);
	hor_inter = hor_intersection_distance(ray, player, data);
	ver_inter = ver_intersection_distance(ray, player, data);
	min = min_point(hor_inter, ver_inter, player);
	ray->intersection.x = min.x;
	ray->intersection.y = min.y;
	tmp.x = player->x;
	tmp.y = player->y;
	ray->distance = distance(tmp, min);
	if (equal_points(min, ver_inter))
		ray->wasHitVertical = true;
	else
		ray->wasHitVertical = false;
}

void	raycasting(t_data *data)
{
	t_player	*player;
	t_ray		ray[NUM_RAYS];
	double		rayangle;
	double		angle_inc;
	int			i;

	player = data->player;
	rayangle = player->rotationAngle - FOV / 2;
	angle_inc = (double)FOV / (double)NUM_RAYS;
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray[i].column = i;
		rayangle = normalize_angle(rayangle);
		cast_ray(data, player, &ray[i], rayangle);
		ray[i].wallStripHeight = get_wall_height(data, &ray[i]);
		ray[i].wallTop = (HEIGHT / 2) - (ray[i].wallStripHeight / 2);
		ray[i].wallBottom = (HEIGHT / 2) + (ray[i].wallStripHeight / 2);
		rayangle += angle_inc;
	}
	i = -1;
	while (++i < NUM_RAYS)
		draw_wall(data, &ray[i]);
	draw_minimap(data, player);
}
