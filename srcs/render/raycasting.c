/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 04:14:03 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/19 02:34:238 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_point ver_intersection_distance(t_ray *ray, t_player *player)
{
	t_point point;
	double  xIntercept;
	double  yIntercept;
	double  xStep;
	double  yStep;

	t_data *data = get_data(NULL);
	// find vertical (y/x)(inter/step) values
	xIntercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
	if (ray->facingRight)
		xIntercept += TILE_SIZE;
	yIntercept = player->y + ((xIntercept - player->x) * tan(ray->angle));
	xStep = TILE_SIZE;
	if (!ray->facingRight)
		xStep *= -1;
	yStep = xStep * tan(ray->angle);
	if ((yStep > 0 && ray->facingUp) || (yStep < 0 && !ray->facingUp))
		yStep *= -1;
	
	// find vertical intersection
	point.x = xIntercept;
	point.y = yIntercept;
	if (!ray->facingRight)
		point.x -= EPSILON;
		// point.x--;
	while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
	{
		if (is_wall_2(point.x, point.y, get_data(NULL)))
			break ;
		else
		{
			point.x += xStep;
			point.y += yStep;
		}
	}
	if (point.x < 0)
		point.x = 0;
	else if (point.x > data->map_data->map.cols * TILE_SIZE)
		point.x = (data->map_data->map.cols * TILE_SIZE) - 1;
	if (point.y < 0)
		point.y = 0;
	else if (point.y > data->map_data->map.rows * TILE_SIZE)
		point.y = (data->map_data->map.rows * TILE_SIZE) - 1;
	return (point);
}

t_point hor_intersection_distance(t_ray *ray, t_player *player)
{
	t_point point;
	double  xIntercept;
	double  yIntercept;
	double  xStep;
	double  yStep;

	t_data *data = get_data(NULL);
	// find horizontal (y/x)(inter/step) values
	yIntercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
	if (!ray->facingUp)
		yIntercept += TILE_SIZE;
	xIntercept = player->x + ((yIntercept - player->y) / tan(ray->angle));
	yStep = TILE_SIZE;
	if (ray->facingUp)
		yStep *= -1;
	xStep = yStep / tan(ray->angle);
	if ((xStep > 0 && !ray->facingRight) || (xStep < 0 && ray->facingRight))
		xStep *= -1;

	// find horizontal intersection
	point.x = xIntercept;
	point.y = yIntercept;
	if (ray->facingUp)
		point.y -= EPSILON;
		// point.y--;
	while ((point.x > 0 && point.x < data->map_data->map.cols * TILE_SIZE) && (point.y > 0 && point.y < data->map_data->map.rows * TILE_SIZE))
	{
		if (is_wall_2(point.x, point.y, get_data(NULL)))
			break ;
		else
		{
			point.x += xStep;
			point.y += yStep;
		}
	}
	if (point.x < 0)
		point.x = 0;
	else if (point.x > data->map_data->map.cols * TILE_SIZE)
		point.x = (data->map_data->map.cols * TILE_SIZE) - 1;
	if (point.y < 0)
		point.y = 0;
	else if (point.y > data->map_data->map.rows * TILE_SIZE)
		point.y = (data->map_data->map.rows * TILE_SIZE) - 1;
	return point;
}

void    cast_ray(t_player *player, t_ray *ray, double rayangle)
{
	set_ray_angle(ray, rayangle);

	// find horizontal and vertical intersection points
	t_point horInter = hor_intersection_distance(ray, player);
	t_point verInter = ver_intersection_distance(ray, player);

	// find the closest intersection point
	t_point min = min_point(horInter, verInter, player);
	ray->intersection.x = min.x;
	ray->intersection.y = min.y;

	// set distance
	t_point tmp;
	tmp.x = player->x;
	tmp.y = player->y;
	ray->distance = distance(tmp, min);
	if (equal_points(min, verInter))
		ray->wasHitVertical = true;
	else
		ray->wasHitVertical = false;
}

void raycasting(t_data *data)
{
	t_player	*player;
	t_ray 		ray[NUM_RAYS];
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
		rayangle = normalizeAngle(rayangle);
		cast_ray(player, &ray[i], rayangle);
		ray[i].wallStripHeight = get_wall_height(data, &ray[i]);
		ray[i].wallTop = (HEIGHT / 2) - (ray[i].wallStripHeight / 2);
		ray[i].wallBottom = (HEIGHT / 2) + (ray[i].wallStripHeight / 2);
		rayangle += angle_inc;
	}
	i = -1;
	while (++i < NUM_RAYS)
		draw_wallStrip(data, &ray[i]);
	draw_minimap(data, player);
}

