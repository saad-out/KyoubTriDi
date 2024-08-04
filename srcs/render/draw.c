/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:08:19 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 09:58:33 by klakbuic         ###   ########.fr       */
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

void	ft_draw_square(t_mlx *mlx, t_draw_square *square)
{
	int	i;
	int	j;
	int	index;

	i = square->x;
	while (i < (square->x + square->size))
	{
		j = square->y;
		while (j < (square->y + square->size))
		{
			index = (j * WIDTH + i) * 4;
			mlx->img.addr[index] = square->color & 0xFF;
			mlx->img.addr[index + 1] = (square->color & 0xFF00) >> 8;
			mlx->img.addr[index + 2] = (square->color & 0xFF0000) >> 16;
			j++;
		}
		i++;
	}
}
