/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:43:36 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/01 12:05:41 by klakbuic         ###   ########.fr       */
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

bool is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	ft_init_player_position(t_player *player, t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_data->map.rows)
	{
		j = 0;
		while (j < map_data->map.cols)
		{
			if (is_player(map_data->map.map[i][j]))
			{
				player->x = (j * TILE_SIZE) + (TILE_SIZE / 2);
				player->y = (i * TILE_SIZE) + (TILE_SIZE / 2);
				if (map_data->map.map[i][j] == 'N')
					player->rotationAngle = 3 * PI / 2;
				else if (map_data->map.map[i][j] == 'S')
					player->rotationAngle = PI / 2;
				else if (map_data->map.map[i][j] == 'E')
					player->rotationAngle = 0;
				else if (map_data->map.map[i][j] == 'W')
					player->rotationAngle = PI;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_init_data(t_data *data)
{
	t_player *player;
	t_map_data *map_data;

	player = data->player;
	map_data = data->map_data;

	map_data->so_texture = NULL;
	map_data->no_texture = NULL;
	map_data->we_texture = NULL;
	map_data->ea_texture = NULL;
	map_data->ceil_color = -1;
	map_data->floor_color = -1;

	player->radius = 100;
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->horMove = 0;
	player->walkSpeed = 0.05 * TILE_SIZE;
	player->turnSpeed = 2 * (PI / 180);
}
