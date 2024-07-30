/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:56:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/30 13:17:40 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ceiling(t_data *data, int column, int wallTop)
{
	ft_draw_line(
		data->mlx,
		column,
		0,
		column,
		wallTop,
		0x111026);
		// 0x213760);
		// 0x203690cc);
		// 0x0087CEFA);
}

float scale(float value, float x0, float y0, float x1, float y1) {
    return x1 + ((value - x0) * (y1 - x1)) / (y0 - x0);
}

void	draw_floor(t_data *data, int column, int wallBottom, double ht)
{
	int	red;
	int	green;
	int	blue;
	int	shaded;
	int color;
	double factor;

	color = 0x634f04;

	double x = 1;
	for (int y = wallBottom; y < HEIGHT; y++)
	{
		red = (color >> 16) & 0xFF;
		green = (color >> 8) & 0xFF;
		blue = color & 0xFF;

		x = ((double)y / (double)HEIGHT);
		// x = sqrt(x);
		x = pow(x, 3);
		// printf("%f\n", x);
		// x *= 100;
		// x = log10(x);
		// printf("x: %f\n", x);
		red *= x;
		green *= x;
		blue *= x;
		shaded = (red << 16) | (green << 8) | blue;
		my_mlx_pixel_put(&data->mlx->img, column, y, shaded);
	}


	// // factor = scale((double)wallBottom, 0, HEIGHT, 0, 1);
	// factor = 10.0;
	// for (int y = wallBottom; y < HEIGHT; y++)
	// {
	// 	// factor = exp(y / 100);
	// 	// if (factor > 1.0)
	// 	// 	factor = 1;
	// 	// factor = 1 / factor;
	// 	// printf("factor %f y %f\n", factor, y / 100);
	// 	red = clamp(red - factor, 0, 255);
	// 	green = clamp(green - factor, 0, 255);
	// 	blue = clamp(blue - factor, 0, 255);
	// 	shaded = (red << 16) | (green << 8) | blue;
	// 	if (y > 500)
	// 		my_mlx_pixel_put(&data->mlx->img, column, y, color);
	// 	else
	// 		my_mlx_pixel_put(&data->mlx->img, column, y, shaded);
	// 	factor += 10.0;
	// 	if (factor > 100.0)
	// 		factor = 10.0;
	// 	// printf("factor: %f\n", factor);
	// }

	// ft_draw_line(
	// 	data->mlx,
	// 	column,
	// 	wallBottom,
	// 	column,
	// 	HEIGHT,
	// 	shaded);
		// 0x00DEB887);
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
	draw_floor(data, ray->column, ray->wallBottom, ray->wallStripHeight);
}

void	draw_minimap(t_data *data, t_player *player)
{
	ft_render_map(data->mlx, data->map_data, player);

}
