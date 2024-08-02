/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:56:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/02 18:33:44 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ceiling(t_data *data, int column, int wallTop)
{
	t_draw_line	line;

	line.x0 = column;
	line.y0 = 0;
	line.x1 = column;
	line.y1 = wallTop;
	line.color = data->map_data->ceil_color;
	ft_draw_line(data->mlx, &line);
}

void	draw_floor(t_data *data, int column, int wallBottom)
{
	t_rgb	c;
	int		color;
	double	x;
	int		y;

	color = data->map_data->floor_color;
	c.red = (color >> 16) & 0xFF;
	c.green = (color >> 8) & 0xFF;
	c.blue = color & 0xFF;
	x = 1;
	y = wallBottom;
	while (y < HEIGHT)
	{
		x = ((double)y / (double)HEIGHT);
		x = pow(x, 3);
		my_mlx_pixel_put(&data->mlx->img, column, y, \
						(((int)(c.red * x) << 16) \
						| ((int)(c.green * x) << 8) \
						| (int)(c.blue * x)));
		y++;
	}
}

void	draw_wall(t_data *data, t_ray *ray)
{
	t_img	texture;

	set_texture(ray, data, &texture);
	if (ray->wallTop < 0)
		ray->wallTop = 0;
	if (ray->wallBottom < 0 || ray->wallBottom > HEIGHT)
		ray->wallBottom = HEIGHT;
	draw_ceiling(data, ray->column, ray->wallTop);
	draw_wall_texture(data, ray);
	draw_floor(data, ray->column, ray->wallBottom);
}
