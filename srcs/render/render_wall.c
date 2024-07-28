/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:56:18 by soutchak          #+#    #+#             */
/*   Updated: 2024/07/28 15:59:36 by klakbuic         ###   ########.fr       */
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
		0x0087CEFA);
}

void	draw_floor(t_data *data, int column, int wallBottom)
{
	ft_draw_line(
		data->mlx,
		column,
		wallBottom,
		column,
		HEIGHT,
		0x00DEB887);
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

void	draw_minimap(t_data *data, t_player *player)
{
	ft_render_map(data->mlx, data->map_data, player);
	ft_draw_circle(
		data->mlx,
		player->x * MINIMAP_SCALE,
		player->y * MINIMAP_SCALE,
		player->radius * MINIMAP_SCALE,
		0x00065535);
	ft_draw_line(
		data->mlx,
		player->x * MINIMAP_SCALE,
		player->y * MINIMAP_SCALE,
		(player->x + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		(player->y + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		0x00000000);
}
