/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:08:19 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/02 10:27:13 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
	int	i;
	int	j;
	int	index;

	i = x;
	while (i < (x + size))
	{
		j = y;
		while (j < (y + size))
		{
			index = (j * WIDTH + i) * 4;
			mlx->img.addr[index] = color & 0xFF;
			mlx->img.addr[index + 1] = (color & 0xFF00) >> 8;
			mlx->img.addr[index + 2] = (color & 0xFF0000) >> 16;
			j++;
		}
		i++;
	}
}

void	ft_draw_line(t_mlx *mlx, t_draw_line *line)
{
	int	err;
	int	e2;
	int	index;

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
	while (true)
	{
		if (line->x0 >= 0 && line->x0 < WIDTH && line->y0 >= 0
			&& line->y0 < HEIGHT)
		{
			index = (line->y0 * mlx->img.line_length + line->x0 * (mlx->img.bpp / 8));
			mlx->img.addr[index] = line->color;
			mlx->img.addr[index + 1] = line->color >> 8;
			mlx->img.addr[index + 2] = line->color >> 16;
		}
		if (line->x0 == line->x1 && line->y0 == line->y1)
		{
			break ;
		}
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

// void	ft_draw_circle(t_mlx *mlx, int xc, int yc, int radius, int color)
// {
// 	t_draw_line	line;
// 	int	x;
// 	int	y;
// 	int	p;

// 	x = radius;
// 	y = 0;
// 	p = 1 - radius;
// 	// Draw initial points on each quadrant
// 	line.x0 = xc - x;
// 	line.y0 = yc;
// 	line.x1 = xc + x;
// 	line.y1 = yc;
// 	line.color = color;
// 	ft_draw_line(mlx, &line);
// 	// Initial horizontal diameter
// 	if (radius > 0)
// 	{
// 		ft_draw_square(mlx, xc - radius, yc, 1, color); // Leftmost point
// 		ft_draw_square(mlx, xc + radius, yc, 1, color); // Rightmost point
// 		ft_draw_square(mlx, xc, yc + radius, 1, color); // Topmost point
// 		ft_draw_square(mlx, xc, yc - radius, 1, color); // Bottommost point
// 	}
// 	// Filling the circle
// 	while (x > y)
// 	{
// 		y++;
// 		// Mid-point is inside or on the perimeter
// 		if (p <= 0)
// 		{
// 			p = p + 2 * y + 1;
// 		}
// 		else
// 		{ // Mid-point is outside the perimeter
// 			x--;
// 			p = p + 2 * y - 2 * x + 1;
// 		}
// 		// All the perimeter points have already been printed
// 		if (x < y)
// 			break ;
// 		// Drawing the horizontal lines for each quadrant
// 		ft_draw_line(mlx, xc - x, yc + y, xc + x, yc + y, color);
// 		ft_draw_line(mlx, xc - x, yc - y, xc + x, yc - y, color);
// 		if (x != y)
// 		{
// 			ft_draw_line(mlx, xc - y, yc + x, xc + y, yc + x, color);
// 			ft_draw_line(mlx, xc - y, yc - x, xc + y, yc - x, color);
// 		}
// 	}
// }
