/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:18:50 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/04 15:46:43 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cast_ray(t_data *data, t_ray *ray, double rayangle, int skip)
{
	t_player	*player;
	t_point		hor_inter;
	t_point		ver_inter;
	t_point		min;
	t_point		tmp;

	player = data->player;
	set_ray_angle(ray, rayangle);
	hor_inter = hor_intersection_distance(ray, player, data, skip);
	ver_inter = ver_intersection_distance(ray, player, data, skip);
	min = min_point(hor_inter, ver_inter, player);
	ray->intersection.x = min.x;
	ray->intersection.y = min.y;
	tmp.x = player->x;
	tmp.y = player->y;
	ray->distance = distance(tmp, min);
	if (equal_points(min, ver_inter))
		ray->was_hit_vertical = true;
	else
		ray->was_hit_vertical = false;
}

void	raycasting(t_data *data)
{
	t_player	*player;
	t_ray		ray[NUM_RAYS];
	double		rayangle;
	double		angle_inc;
	int			i;

	player = data->player;
	rayangle = player->rotation_angle - FOV / 2;
	angle_inc = (double)FOV / (double)NUM_RAYS;
	i = -1;
	while (++i < NUM_RAYS)
	{
		ray[i].column = i;
		rayangle = normalize_angle(rayangle);
		cast_ray(data, &ray[i], rayangle, 1);
		ray[i].wall_strip_height = get_wall_height(data, &ray[i]);
		ray[i].wall_top = (HEIGHT / 2) - (ray[i].wall_strip_height / 2);
		ray[i].wall_bottom = (HEIGHT / 2) + (ray[i].wall_strip_height / 2);
		rayangle += angle_inc;
	}
	i = -1;
	while (++i < NUM_RAYS)
		draw_wall(data, &ray[i]);
}
