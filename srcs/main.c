/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/27 15:57:14 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void ft_render_map(t_mlx *mlx, t_map_data *map_data)
{
		for (int i = 0; i < map_data->map.rows; i++)
	{
		for (int j = 0; j < map_data->map.cols; j++)
		{
			if (map_data->map.map[i][j] == '1')
				ft_draw_square(mlx,
								j * TILE_SIZE * MINIMAP_SCALE,
								i * TILE_SIZE * MINIMAP_SCALE,
								TILE_SIZE * MINIMAP_SCALE,
								0x00FF0000);
			else
				ft_draw_square(mlx,
								j * TILE_SIZE * MINIMAP_SCALE,
								i * TILE_SIZE * MINIMAP_SCALE,
								TILE_SIZE * MINIMAP_SCALE,
								0x00FFFFFF);
		}
	}
}

bool	cannot_move(double x, double y, t_data *data)
{
	int	playerSize = 30;

	return (
		is_wall_1(x - playerSize, y - playerSize, data) ||
		is_wall_1(x + playerSize, y - playerSize, data) ||
		is_wall_1(x - playerSize, y + playerSize, data) ||
		is_wall_1(x + playerSize, y + playerSize, data)
	);
}

void render_image(t_data *data)
{
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
	data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
	ft_render_map(data->mlx, data->map_data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
}

void	handle_collision(double *nx, double *ny, double dx, double dy, t_data *data)
{
	t_player	*player;

	player = data->player;
	if (!cannot_move(player->x + dx, player->y + dy, data))
	{
		*nx = player->x + dx;
		*ny = player->y + dy;
	}
	else if (!cannot_move(player->x + dx, player->y, data))
	{
		*nx = player->x + dx;
		*ny = player->y;
	}
	else if (!cannot_move(player->x, player->y + dy, data))
	{
		*nx = player->x;
		*ny = player->y + dy;
	}
	else
	{
		printf(RED"Error asat\n"RESET);
		*nx = player->x;
		*ny = player->y;
	}
}

void move_player(t_data *data)
{
	t_player *player;
	double movestep;
	double next_y;
	double next_x;
	double	xstep;
	double	ystep;
	
	player = data->player;
	movestep = player->walkDirection * player->walkSpeed;
	player->rotationAngle += player->turnDirection * player->turnSpeed;
	xstep = cos(player->rotationAngle + player->horMove) * movestep;
	ystep = sin(data->player->rotationAngle + player->horMove) * movestep;
	handle_collision(&next_x, &next_y, xstep, ystep, data);
	data->player->x = next_x;
	data->player->y = next_y;
	render_image(data);
}

t_data	*get_data(t_data *data)
{
	static t_data *tmp = NULL;

	if (data)
		tmp = data;
	return (tmp);
}

void	load_textures(t_map_data *map_data, t_mlx *mlx)
{
	int	width;
	int	height;


	// // Calculate the number of pixels
    // int num_pixels = width * height;
    // int bytes_per_pixel = map_data->no_texture_img.bpp / 8;

    // // Print pixel data
    // for (int i = 0; i < num_pixels; i++) {
    //     int pixel_offset = i * bytes_per_pixel;
    //     unsigned int color = *(unsigned int *)(map_data->no_texture_img.addr + pixel_offset);
    //     printf("NO[%d]: %#x\n", i, color);
    // }
	// sleep(5);
	
	map_data->no_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map_data->no_texture, &map_data->no_texture_img.width, &map_data->no_texture_img.height);
	map_data->no_texture_img.addr = mlx_get_data_addr(map_data->no_texture_img.img_ptr, &map_data->no_texture_img.bpp, &map_data->no_texture_img.line_length, &map_data->no_texture_img.endian);
	printf(" ===================== 1111111 =====================\n");

	map_data->so_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map_data->so_texture, &map_data->so_texture_img.width, &map_data->so_texture_img.height);
	map_data->so_texture_img.addr = mlx_get_data_addr(map_data->so_texture_img.img_ptr, &map_data->so_texture_img.bpp, &map_data->so_texture_img.line_length, &map_data->so_texture_img.endian);
	printf(" ===================== 222222 =====================\n");

	map_data->we_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map_data->we_texture, &map_data->we_texture_img.width, &map_data->we_texture_img.height);
	map_data->we_texture_img.addr = mlx_get_data_addr(map_data->we_texture_img.img_ptr, &map_data->we_texture_img.bpp, &map_data->we_texture_img.line_length, &map_data->we_texture_img.endian);
	printf(" ===================== 333333 =====================\n");

	map_data->ea_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, map_data->ea_texture, &map_data->ea_texture_img.width, &map_data->ea_texture_img.height);
	map_data->ea_texture_img.addr = mlx_get_data_addr(map_data->ea_texture_img.img_ptr, &map_data->ea_texture_img.bpp, &map_data->ea_texture_img.line_length, &map_data->ea_texture_img.endian);
	printf(" ===================== 44444 =====================\n");

	printf("Done loading textures\n");
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	t_map_data map_data;
	t_player player;
	t_mlx mlx;
	t_data data;
	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;

	get_data(&data);
	ft_init_mlx(&mlx);
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	ft_init_player_position(&player, &map_data);
	load_textures(&map_data, &mlx);
	ft_render_map(&mlx, &map_data);
	raycasting(&data);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.win, 3, 1L << 1, key_realse, &data);
	mlx_loop(mlx.mlx_ptr);
}