/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 13:07:59 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/04 11:08:42 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	compute_hor_intercept(t_player *p, t_ray *ray, double *xI, double *yI)
{
	*yI = floor(p->y / TILE_SIZE) * TILE_SIZE;
	if (!ray->facing_up)
		*yI += TILE_SIZE;
	*xI = p->x + ((*yI - p->y) / tan(ray->angle));
}

void	compute_hor_step(t_ray *ray, double *xS, double *yS)
{
	*yS = TILE_SIZE;
	if (ray->facing_up)
		*yS *= -1;
	*xS = *yS / tan(ray->angle);
	if ((*xS > 0 && !ray->facing_right) || (*xS < 0 && ray->facing_right))
		*xS *= -1;
}

t_point	hor_intersection_distance(t_ray *ray, t_player *player, \
									t_data *data, int skip)
{
	t_point	point;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	compute_hor_intercept(player, ray, &x_intercept, &y_intercept);
	compute_hor_step(ray, &x_step, &y_step);
	point.x = x_intercept;
	point.y = y_intercept;
	if (ray->facing_up)
		point.y -= EPSILON;
	while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) \
			&& (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
	{
		if (is_wall_2(point.x, point.y, data) \
			|| is_door(data, point.x, point.y, skip))
			break ;
		else
		{
			point.x += x_step;
			point.y += y_step;
		}
	}
	return (point_adjustment(&point, data), point);
}
