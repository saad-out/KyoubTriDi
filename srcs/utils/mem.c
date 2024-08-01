/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:52:33 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/01 12:16:59 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win);
	if (mlx->img.img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
}

void	free_all_mem(t_data *data)
{
	if (data->mlx)
		free_mlx(data->mlx);
	if (data->map_data)
	{
		if (data->map_data->map.map)
			free_split(data->map_data->map.map);
	}
}