/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:08:19 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/27 15:18:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
	{
		return ;
	}
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
	for (int i = x; i < x + size; i++)
	{
		for (int j = y; j < y + size; j++)
		{
			int index = (j * WIDTH + i) * 4;
			mlx->img.addr[index] = color & 0xFF;
			mlx->img.addr[index + 1] = (color & 0xFF00) >> 8;
			mlx->img.addr[index + 2] = (color & 0xFF0000) >> 16;
		}
	}
}

void ft_draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

	while (1) {
    if (x0 >= 0 && x0 < WIDTH && y0 >= 0 && y0 < HEIGHT) {
        int index = (y0 * mlx->img.line_length + x0 * (mlx->img.bpp / 8));
        // printf("Drawing pixel at (%d, %d) with index %d\n", x0, y0, index);
        mlx->img.addr[index] = color;
        mlx->img.addr[index + 1] = color >> 8;
        mlx->img.addr[index + 2] = color >> 16;
    }

    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; }
    if (e2 <= dx) { err += dx; y0 += sy; }
	}
}

void	ft_draw_circle(t_mlx *mlx, int xc, int yc, int radius, int color)
{
	int x = radius;
	int y = 0;
	int p = 1 - radius;

	// Draw initial points on each quadrant
	ft_draw_line(mlx, xc - x, yc, xc + x, yc, color);
		// Initial horizontal diameter

	if (radius > 0)
	{
		ft_draw_square(mlx, xc - radius, yc, 1, color); // Leftmost point
		ft_draw_square(mlx, xc + radius, yc, 1, color); // Rightmost point
		ft_draw_square(mlx, xc, yc + radius, 1, color); // Topmost point
		ft_draw_square(mlx, xc, yc - radius, 1, color); // Bottommost point
	}

	// Filling the circle
	while (x > y)
	{
		y++;

		// Mid-point is inside or on the perimeter
		if (p <= 0)
		{
			p = p + 2 * y + 1;
		}
		else
		{ // Mid-point is outside the perimeter
			x--;
			p = p + 2 * y - 2 * x + 1;
		}

		// All the perimeter points have already been printed
		if (x < y)
			break ;

		// Drawing the horizontal lines for each quadrant
		ft_draw_line(mlx, xc - x, yc + y, xc + x, yc + y, color);
		ft_draw_line(mlx, xc - x, yc - y, xc + x, yc - y, color);

		if (x != y)
		{
			ft_draw_line(mlx, xc - y, yc + x, xc + y, yc + x, color);
			ft_draw_line(mlx, xc - y, yc - x, xc + y, yc - x, color);
		}
	}
}
