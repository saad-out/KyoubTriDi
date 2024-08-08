/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:45:41 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 09:46:19 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_pixels_in_image(t_mlx *mlx, t_draw_line *line, int index)
{
	mlx->img.addr[index] = line->color;
	mlx->img.addr[index + 1] = line->color >> 8;
	mlx->img.addr[index + 2] = line->color >> 16;
}

void	render_line(t_mlx *mlx, t_draw_line *line, int e2, int err)
{
	int	index;

	while (true)
	{
		if (line->x0 >= 0 && line->x0 < WIDTH && line->y0 >= 0
			&& line->y0 < HEIGHT)
		{
			index = (line->y0 * mlx->img.line_length + line->x0 * (mlx->img.bpp
						/ 8));
			draw_pixels_in_image(mlx, line, index);
		}
		if (line->x0 == line->x1 && line->y0 == line->y1)
			break ;
		e2 = 2 * err;
		if (e2 >= line->dy)
		{
			err += line->dy;
			line->x0 += line->sx;
		}
		if (e2 <= line->dx)
		{
			err += line->dx;
			line->y0 += line->sy;
		}
	}
}

void	ft_draw_line(t_mlx *mlx, t_draw_line *line)
{
	int	err;
	int	e2;

	e2 = 0;
	line->dx = abs(line->x1 - line->x0);
	if (line->x0 < line->x1)
		line->sx = 1;
	else
		line->sx = -1;
	line->dy = -abs(line->y1 - line->y0);
	if (line->y0 < line->y1)
		line->sy = 1;
	else
		line->sy = -1;
	err = line->dx + line->dy;
	render_line(mlx, line, e2, err);
}
