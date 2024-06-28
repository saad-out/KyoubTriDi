/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/06/27 11:26:28 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(void)
{
	int map[][5] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1}
	};

	t_mlx *mlx;
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	ft_init(mlx);
	for (int i = 0; i < MAP_NUM_COLS; i++)
	{
		for (int j = 0; j < MAP_NUM_ROWS; j++)
		{
			if (map[i][j] == 1)
				draw_square(&mlx->img, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, 0xFFFFFFFF);
		}
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}