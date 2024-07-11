/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/09 10:45:07 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
	int	topIndex;
	int	bottomIndex;
	int	leftIndex;
	int	rightIndex;

	// Draw top and bottom borders
	for (int j = x; j < x + size; j++)
	{
		topIndex = (y * mlx->img.line_length + j * (mlx->img.bpp / 8));
		mlx->img.addr[topIndex] = color;
		mlx->img.addr[topIndex + 1] = color >> 8;
		mlx->img.addr[topIndex + 2] = color >> 16;
		bottomIndex = ((y + size - 1) * mlx->img.line_length + j * (mlx->img.bpp
					/ 8));
		mlx->img.addr[bottomIndex] = color;
		mlx->img.addr[bottomIndex + 1] = color >> 8;
		mlx->img.addr[bottomIndex + 2] = color >> 16;
	}
	// Draw left and right borders
	for (int i = y; i < y + size; i++)
	{
		leftIndex = (i * mlx->img.line_length + x * (mlx->img.bpp / 8));
		mlx->img.addr[leftIndex] = color;
		mlx->img.addr[leftIndex + 1] = color >> 8;
		mlx->img.addr[leftIndex + 2] = color >> 16;
		rightIndex = (i * mlx->img.line_length + (x + size - 1) * (mlx->img.bpp
					/ 8));
		mlx->img.addr[rightIndex] = color;
		mlx->img.addr[rightIndex + 1] = color >> 8;
		mlx->img.addr[rightIndex + 2] = color >> 16;
	}
}

void	ft_draw_circle(t_mlx *mlx, int x, int y, int radius, int color)
{
	int	x1;
	int	y1;

	for (int i = 0; i < 360; i++)
	{
		x1 = x + radius * cos(i * PI / 180);
		y1 = y + radius * sin(i * PI / 180);
		ft_draw_square(mlx, x1, y1, 1, color);
	}
}

void	ft_render_player(t_mlx *mlx, t_player *player)
{
	ft_draw_circle(mlx, player->x, player->y, player->radius, 0x00065535);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	t_map_data map_data;
	// INIT:
	map_data.so_texture = NULL;
	map_data.no_texture = NULL;
	map_data.we_texture = NULL;
	map_data.ea_texture = NULL;
	map_data.ceil_color = -1;
	map_data.floor_color = -1;
	parse_map_file(av[1], &map_data);
	t_mlx mlx;
	ft_init(&mlx);
	// Render map:
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			if (map_data.map.map[i][j] == '1')
				ft_draw_square(&mlx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE,
					0x00FF0000);
			else if (map_data.map.map[i][j] == '0')
				ft_draw_square(&mlx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE,
					0x00FFFFFF);
		}
	}
	// Render player:
	t_player player;
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.radius = 7;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = PI / 2;
	player.walkSpeed = 2;
	player.turnSpeed = 2 * (PI / 180);
	ft_render_player(&mlx, &player);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
}