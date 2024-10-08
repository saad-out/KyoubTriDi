/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:51:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/04 11:11:49 by klakbuic         ###   ########.fr       */
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

	dis_from_top = y + (ray->wall_strip_height / 2) - (HEIGHT / 2);
	return ((1LL * dis_from_top * texture->height + ray->wall_strip_height / 2) \
			/ ray->wall_strip_height);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

int	add_shading(t_ray *ray, int color)
{
	t_rgb	c;
	int		shaded;
	double	factor;

	c.red = (color >> 16) & 0xFF;
	c.green = (color >> 8) & 0xFF;
	c.blue = color & 0xFF;
	factor = log10(ray->wall_strip_height / 35);
	c.red = clamp(c.red * factor, 0, 255);
	c.green = clamp(c.green * factor, 0, 255);
	c.blue = clamp(c.blue * factor, 0, 255);
	shaded = (c.red << 16) | (c.green << 8) | c.blue;
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
	if (ray->was_hit_vertical)
		texel_x = (int)ray->intersection.y % TILE_SIZE;
	else
		texel_x = (int)ray->intersection.x % TILE_SIZE;
	texel_x = (texel_x * texture.width) / TILE_SIZE;
	y = ray->wall_top;
	while (y < ray->wall_bottom)
	{
		texel_y = get_texel_y(ray, y, &texture);
		texel_y = texel_y % texture.height;
		color = get_texture_color(texel_x, texel_y, texture);
		color = add_shading(ray, color);
		my_mlx_pixel_put(&data->mlx->img, ray->column, y, color);
		y++;
	}
}
