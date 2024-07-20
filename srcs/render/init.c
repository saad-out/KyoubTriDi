/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:43:36 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/20 11:58:54 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (NULL == mlx->mlx_ptr)
	{
		free(mlx);
	}
	mlx->win = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "cub3D");
	if (NULL == mlx->win)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx);
	}
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	if (NULL == mlx->img.img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
			&mlx->img.line_length, &mlx->img.endian);
}
