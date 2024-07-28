/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:51:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/28 13:25:37 by soutchak         ###   ########.fr       */
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
	while (y < ray->wallBottom)
	{
		texel_y = get_texel_y(ray, y, &texture);
		texel_y = texel_y % texture.height;
		color = get_texture_color(texel_x, texel_y, texture);
		my_mlx_pixel_put(&data->mlx->img, ray->column, y, color);
		y++;
	}
}
