/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:51:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/29 17:18:20 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_texture_color(int x, int y, t_img texture)
{
	int	color;
	int	*addr;

	addr = (int *)texture.addr;
	color = addr[y * texture.width + x];
	return (color);
}

int	get_texel_y(t_ray *ray, int y, t_img *texture)
{
	int	dis_from_top;

	dis_from_top = y + (ray->wallStripHeight / 2) - (HEIGHT / 2);
	return ((1LL * dis_from_top * texture->height + ray->wallStripHeight / 2) \
			/ ray->wallStripHeight);
}

int clamp(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int	add_shading(t_ray *ray, int color)
{
	int	red;
	int	green;
	int	blue;
	int	shaded;
	double factor;

	red = (color >> 16) & 0xFF;
	green = (color >> 8) & 0xFF;
	blue = color & 0xFF;
	factor = log10(ray->wallStripHeight / 35);

	red = clamp(red * factor, 0, 255);
	green = clamp(green * factor, 0, 255);
	blue =  clamp(blue * factor, 0, 255);
	shaded = (red << 16) | (green << 8) | blue;
	return (shaded);
}

void	draw_wall_texture(t_data *data, t_ray *ray)
{
	int		texel_x;
	int		y;
	int		texel_y;
	int		color;
	t_img	texture;

	set_texture(ray, data, &texture);
	if (ray->wasHitVertical)
		texel_x = (int)ray->intersection.y % TILE_SIZE;
	else
		texel_x = (int)ray->intersection.x % TILE_SIZE;
	texel_x = (texel_x * texture.width) / TILE_SIZE;
	y = ray->wallTop;
	// printf("\n\n");
	while (y < ray->wallBottom)
	{
		// printf("===> %f\n", ray->wallStripHeight);
		texel_y = get_texel_y(ray, y, &texture);
		texel_y = texel_y % texture.height;
		color = get_texture_color(texel_x, texel_y, texture);
		// printf("==> old %d\n", color);
		color = add_shading(ray, color);
		// printf("==> new %d\n", color);
		my_mlx_pixel_put(&data->mlx->img, ray->column, y, color);
		y++;
	}
}
