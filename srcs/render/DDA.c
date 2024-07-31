/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 12:35:26 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/31 11:15:41 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	compute_ver_intercept(t_player *p, t_ray *ray, double *xI, double *yI)
{
	*xI = floor(p->x / TILE_SIZE) * TILE_SIZE;
	if (ray->facingRight)
		*xI += TILE_SIZE;
	*yI = p->y + ((*xI - p->x) * tan(ray->angle));
}

void	compute_ver_step(t_ray *ray, double *xS, double *yS)
{
	*xS = TILE_SIZE;
	if (!ray->facingRight)
		*xS *= -1;
	*yS = *xS * tan(ray->angle);
	if ((*yS > 0 && ray->facingUp) || (*yS < 0 && !ray->facingUp))
		*yS *= -1;
}

t_point	ver_intersection_distance(t_ray *ray, t_player *player, t_data *data, int skip)
{
	t_point	point;
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	compute_ver_intercept(player, ray, &x_intercept, &y_intercept);
	compute_ver_step(ray, &x_step, &y_step);
	point.x = x_intercept;
	point.y = y_intercept;
	if (!ray->facingRight)
		point.x -= EPSILON;
	while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) \
			&& (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
	{
		if (is_wall_2(point.x, point.y, data) || is_door(data, point.x, point.y, skip))
			break ;
		else
		{
			point.x += x_step;
			point.y += y_step;
		}
	}
	point_adjustment(&point, data);
	return (point);
}

void	point_adjustment(t_point *point, t_data *data)
{
	if (point->x < 0)
		point->x = 0;
	else if (point->x > data->map_data->map.cols * TILE_SIZE)
		point->x = (data->map_data->map.cols * TILE_SIZE) - 1;
	if (point->y < 0)
		point->y = 0;
	else if (point->y > data->map_data->map.rows * TILE_SIZE)
		point->y = (data->map_data->map.rows * TILE_SIZE) - 1;
}
