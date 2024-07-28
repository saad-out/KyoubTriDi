/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:51:02 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/28 11:53:51 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int    get_texture_color(int x, int y, t_img texture)
{
	int color;
	int *addr;

	addr = (int *)texture.addr;
	color = addr[y * texture.width + x];
	return (color);
}

int	get_texelY(t_ray *ray, int y, t_img *texture)
{
	int	distanceFromTop;

	distanceFromTop = y + (ray->wallStripHeight / 2) - (HEIGHT / 2);
	return ((1LL* distanceFromTop * texture->height + ray->wallStripHeight/2)/ ray->wallStripHeight);
}

void	draw_wall_texture(t_data *data, t_ray *ray)
{
	int		texelX;
	int		y;
	int		texelY;
	int		color;
	t_img	texture;

	set_texture(ray, data, &texture);
	if (ray->wasHitVertical)
		texelX = (int)ray->intersection.y % TILE_SIZE;
	else
		texelX = (int)ray->intersection.x % TILE_SIZE;
	texelX = (texelX * texture.width) / TILE_SIZE;
	y = ray->wallTop;
	while (y < ray->wallBottom)
	{
		texelY = get_texelY(ray, y, &texture);
		texelY = texelY % texture.height;
		color = get_texture_color(texelX, texelY, texture);
		my_mlx_pixel_put(&data->mlx->img, ray->column, y, color);
		y++;
	}
}
