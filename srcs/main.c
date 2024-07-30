/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/30 10:59:00 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img flame;
int	index_ogbi = 0;

void ft_render_map(t_mlx *mlx, t_map_data *map_data, t_player *player)
{
	double player_x;
	double player_y;
	int		start_x;
	int		start_y;
	int		end_x;
	int		end_y;
	int		imran_x;
	int		imran_y;
	int view_distance = 5;
	
	
	player_x = player->x / TILE_SIZE;
	player_y = player->y / TILE_SIZE;

	start_x = player_x - view_distance;
	start_y = player_y - view_distance;
	end_x = player_x + view_distance;
	end_y = player_y + view_distance;
	
	while (start_x < 0)
	{
		start_x++;
		end_x++;
	}
	while (start_y < 0)
	{
		start_y++;
		end_y++;
	}
	while (end_x > map_data->map.cols)
	{
		end_x--;
		start_x--;
	}
	while (end_y > map_data->map.rows)
	{
		end_y--;
		start_y--;
	}
	int offsety = 0;
	//printf(RED"px=%d, py=%d", player_x, player_y);
	for (int i = start_y; i < end_y; i++)
	{
		int offsetx = 0;
		for (int j = start_x; j < end_x; j++)
		{
			printf("");
			if (map_data->map.map[i][j] == '1')
				ft_draw_square(mlx,
								offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
								offsety * (int)(TILE_SIZE * MINIMAP_SCALE),
								(int)(TILE_SIZE * MINIMAP_SCALE),
								0x00FF0000);
			else
				ft_draw_square(mlx,
								offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
								offsety * (int)(TILE_SIZE * MINIMAP_SCALE),
								(int)(TILE_SIZE * MINIMAP_SCALE),
								0x00FFFFFF);
			
			if (i == (int)player_y && j == (int)player_x)
			{
				imran_x = offsetx;
				imran_y = offsety;
			}
			offsetx++;
		}
		offsety++;
	}
	int posx, posy;
	posx = (imran_x + player_x - (int)player_x) * TILE_SIZE;
	posy = (imran_y + player_y - (int)player_y) * TILE_SIZE;
	ft_draw_circle(
		mlx,
		posx * MINIMAP_SCALE,
		posy * MINIMAP_SCALE,
		player->radius * MINIMAP_SCALE,
		0x00065535);
	ft_draw_line(
		mlx,
		posx * MINIMAP_SCALE,
		posy * MINIMAP_SCALE,
		(posx + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		(posy + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		0x00000000);
		// printf(" ===> %d\n", player->rotationAngle);
}
// void ft_render_map(t_mlx *mlx, t_map_data *map_data)
// {
// 		for (int i = 0; i < map_data->map.rows; i++)
// 	{
// 		for (int j = 0; j < map_data->map.cols; j++)
// 		{
// 			if (map_data->map.map[i][j] == '1')
// 				ft_draw_square(mlx,
// 								j * TILE_SIZE * MINIMAP_SCALE,
// 								i * TILE_SIZE * MINIMAP_SCALE,
// 								TILE_SIZE * MINIMAP_SCALE,
// 								0x00FF0000);
// 			else
// 				ft_draw_square(mlx,
// 								j * TILE_SIZE * MINIMAP_SCALE,
// 								i * TILE_SIZE * MINIMAP_SCALE,
// 								TILE_SIZE * MINIMAP_SCALE,
// 								0x00FFFFFF);
// 		}
// 	}
// }

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

void paste_part_into_image(t_img *img1, t_img *img2, t_action action) 
{
    int i;
	int j;
	unsigned int *img1_addr;
	unsigned int *img2_addr;

    i = 0;
    img1_addr = (unsigned int *)img1->addr;
	img2_addr = (unsigned int *)img2->addr;
	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			if (img1_addr[j + i * img1->width] != RGBA)
				img2_addr[(action.x + j) + ((i + action.y) * (img2->width))] = img1_addr[j + i * img1->width];
			j++;
		}
		i++;
	}
}


void render_image(t_data *data)
{
	t_img *test;

	if (index_ogbi >= 30)
		index_ogbi = 0;
	if (index_ogbi < 10)
		flame = data->map_data->flame_texture_img;
	else if (index_ogbi < 20)
		flame = data->map_data->flame2_texture_img;
	else
		flame = data->map_data->flame3_texture_img;
	test = &data->mlx->img;
	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
	data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
	ft_render_map(data->mlx, data->map_data, data->player);
	raycasting(data);
	data->mlx->img.width = WIDTH;
	data->mlx->img.height = HEIGHT;
	paste_part_into_image(&flame, &data->mlx->img, (t_action){0, 0});
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
	// usleep(100000);
	index_ogbi++;
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
	map_data->flame_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/1bg.xpm", &map_data->flame_texture_img.width, &map_data->flame_texture_img.height);
	map_data->flame_texture_img.addr = mlx_get_data_addr(map_data->flame_texture_img.img_ptr, &map_data->flame_texture_img.bpp, &map_data->flame_texture_img.line_length, &map_data->flame_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame_texture_img.width, map_data->flame_texture_img.height);
	
	map_data->flame2_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/2bg.xpm", &map_data->flame2_texture_img.width, &map_data->flame2_texture_img.height);
	map_data->flame2_texture_img.addr = mlx_get_data_addr(map_data->flame2_texture_img.img_ptr, &map_data->flame2_texture_img.bpp, &map_data->flame2_texture_img.line_length, &map_data->flame2_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame2_texture_img.width, map_data->flame2_texture_img.height);
	
	map_data->flame3_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/3bg.xpm", &map_data->flame3_texture_img.width, &map_data->flame3_texture_img.height);
	map_data->flame3_texture_img.addr = mlx_get_data_addr(map_data->flame3_texture_img.img_ptr, &map_data->flame3_texture_img.bpp, &map_data->flame3_texture_img.line_length, &map_data->flame3_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame3_texture_img.width, map_data->flame3_texture_img.height);

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

int ogbi(void *d)
{
	t_data *data = (t_data *)d;
	static t_img	khawya;

	if (index_ogbi >= 30)
		index_ogbi = 0;
	if (index_ogbi < 10)
		flame = data->map_data->flame_texture_img;
	else if (index_ogbi < 20)
		flame = data->map_data->flame2_texture_img;
	else
		flame = data->map_data->flame3_texture_img;
	raycasting(data);
	paste_part_into_image(&flame, &data->mlx->img, (t_action){0, 0});
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
	// usleep(100000);
	index_ogbi++;
	return (0);
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
	ft_render_map(&mlx, &map_data, &player);
	mlx_loop_hook(mlx.mlx_ptr, ogbi,&data);
	// raycasting(&data);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.win, 3, 1L << 1, key_realse, &data);
	mlx_loop(mlx.mlx_ptr);
}
