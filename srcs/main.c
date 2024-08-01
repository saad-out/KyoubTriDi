/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/01 11:11:07 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img flame;
int	index_ogbi = 0;

void ft_render_map(t_mlx *mlx, t_map_data *map_data, t_player *player)
{
	double	player_x;
	double	player_y;
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
		if (end_x < map_data->map.cols)
			end_x++;
	}
	while (start_y < 0)
	{
		start_y++;
		if (end_y < map_data->map.rows)
			end_y++;
	}
	while (end_x > map_data->map.cols)
	{
		end_x--;
		if (start_x > 0)
			start_x--;
	}
	while (end_y > map_data->map.rows)
	{
		end_y--;
		if (start_y > 0)
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
								0x00666340);
								// 0x00FF0000);
			else if (map_data->map.map[i][j] == '2')
				ft_draw_square(mlx,
								offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
								offsety * (int)(TILE_SIZE * MINIMAP_SCALE),
								(int)(TILE_SIZE * MINIMAP_SCALE),
								0x000000FF);
			else if (map_data->map.map[i][j] == '3')
				ft_draw_square(mlx,
								offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
								offsety * (int)(TILE_SIZE * MINIMAP_SCALE),
								(int)(TILE_SIZE * MINIMAP_SCALE),
								0x0000FF00);
			else if (map_data->map.map[i][j] != ' ')
				ft_draw_square(mlx,
								offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
								offsety * (int)(TILE_SIZE * MINIMAP_SCALE),
								(int)(TILE_SIZE * MINIMAP_SCALE),
								0x808080);
								// 0x00FFFFFF);
			
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
		0x283fd1);
		// 0x00065535);
	ft_draw_line(
		mlx,
		posx * MINIMAP_SCALE,
		posy * MINIMAP_SCALE,
		(posx + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		(posy + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		0x283fd1);
		// 0x00000000);
		// printf(" ===> %d\n", player->rotationAngle);
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
			if (img1_addr[j + i * img1->width] != RGBA && (action.x + j) < WIDTH && (i + action.y) < HEIGHT)
				img2_addr[(action.x + j) + ((i + action.y) * (img2->width))] = img1_addr[j + i * img1->width];
			j++;
		}
		i++;
	}
}


// void render_image(t_data *data)
// {
// 	t_img *test;

// 	if (index_ogbi >= 11)
// 		index_ogbi = 0;
// 	if (index_ogbi == 0)
// 		flame = data->map_data->flame_texture_img;
// 	else if (index_ogbi == 1)
// 		flame = data->map_data->flame2_texture_img;
// 	else if (index_ogbi == 2)
// 		flame = data->map_data->flame3_texture_img;
// 	else if (index_ogbi == 3)
// 		flame = data->map_data->flame4_texture_img;
// 	else if (index_ogbi == 4)
// 		flame = data->map_data->flame5_texture_img;
// 	else if (index_ogbi == 5)
// 		flame = data->map_data->flame6_texture_img;
// 	else if (index_ogbi == 6)
// 		flame = data->map_data->flame7_texture_img;
// 	else if (index_ogbi == 7)
// 		flame = data->map_data->flame8_texture_img;
// 	else if (index_ogbi == 8)
// 		flame = data->map_data->flame9_texture_img;
// 	else if (index_ogbi == 9)
// 		flame = data->map_data->flame10_texture_img;
// 	else if (index_ogbi == 10)
// 		flame = data->map_data->flame11_texture_img;
// 	test = &data->mlx->img;
// 	mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
// 	data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
// 	ft_render_map(data->mlx, data->map_data, data->player);
// 	raycasting(data);
// 	data->mlx->img.width = WIDTH;
// 	data->mlx->img.height = HEIGHT;
// 	printf(RED"render\n"RESET);
// 	paste_part_into_image(&flame, &data->mlx->img, (t_action){0, 0});
// 	// mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
// 	// usleep(100000);
// 	index_ogbi++;
// }

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

	map_data->door_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/creepydoor.xpm", &map_data->door_img.width, &map_data->door_img.height);
	map_data->door_img.addr = mlx_get_data_addr(map_data->door_img.img_ptr, &map_data->door_img.bpp, &map_data->door_img.line_length, &map_data->door_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->door_img.width, map_data->door_img.height);

	map_data->flame_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/1bg.xpm", &map_data->flame_texture_img.width, &map_data->flame_texture_img.height);
	map_data->flame_texture_img.addr = mlx_get_data_addr(map_data->flame_texture_img.img_ptr, &map_data->flame_texture_img.bpp, &map_data->flame_texture_img.line_length, &map_data->flame_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame_texture_img.width, map_data->flame_texture_img.height);
	
	map_data->flame2_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/2bg.xpm", &map_data->flame2_texture_img.width, &map_data->flame2_texture_img.height);
	map_data->flame2_texture_img.addr = mlx_get_data_addr(map_data->flame2_texture_img.img_ptr, &map_data->flame2_texture_img.bpp, &map_data->flame2_texture_img.line_length, &map_data->flame2_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame2_texture_img.width, map_data->flame2_texture_img.height);
	
	map_data->flame3_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/3bg.xpm", &map_data->flame3_texture_img.width, &map_data->flame3_texture_img.height);
	map_data->flame3_texture_img.addr = mlx_get_data_addr(map_data->flame3_texture_img.img_ptr, &map_data->flame3_texture_img.bpp, &map_data->flame3_texture_img.line_length, &map_data->flame3_texture_img.endian);
	printf(" ===================== 000000 ===================== %d %d\n", map_data->flame3_texture_img.width, map_data->flame3_texture_img.height);

	// map_data->flame4_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/4.xpm", &map_data->flame4_texture_img.width, &map_data->flame4_texture_img.height);
	// map_data->flame4_texture_img.addr = mlx_get_data_addr(map_data->flame4_texture_img.img_ptr, &map_data->flame4_texture_img.bpp, &map_data->flame4_texture_img.line_length, &map_data->flame4_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame4_texture_img.width, map_data->flame4_texture_img.height);

	// map_data->flame5_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/5.xpm", &map_data->flame5_texture_img.width, &map_data->flame5_texture_img.height);
	// map_data->flame5_texture_img.addr = mlx_get_data_addr(map_data->flame5_texture_img.img_ptr, &map_data->flame5_texture_img.bpp, &map_data->flame5_texture_img.line_length, &map_data->flame5_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame5_texture_img.width, map_data->flame5_texture_img.height);

	// map_data->flame6_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/6.xpm", &map_data->flame6_texture_img.width, &map_data->flame6_texture_img.height);
	// map_data->flame6_texture_img.addr = mlx_get_data_addr(map_data->flame6_texture_img.img_ptr, &map_data->flame6_texture_img.bpp, &map_data->flame6_texture_img.line_length, &map_data->flame6_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame6_texture_img.width, map_data->flame6_texture_img.height);

	// map_data->flame7_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/7.xpm", &map_data->flame7_texture_img.width, &map_data->flame7_texture_img.height);
	// map_data->flame7_texture_img.addr = mlx_get_data_addr(map_data->flame7_texture_img.img_ptr, &map_data->flame7_texture_img.bpp, &map_data->flame7_texture_img.line_length, &map_data->flame7_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame7_texture_img.width, map_data->flame7_texture_img.height);
	
	// map_data->flame8_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/8.xpm", &map_data->flame8_texture_img.width, &map_data->flame8_texture_img.height);
	// map_data->flame8_texture_img.addr = mlx_get_data_addr(map_data->flame8_texture_img.img_ptr, &map_data->flame8_texture_img.bpp, &map_data->flame8_texture_img.line_length, &map_data->flame8_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame8_texture_img.width, map_data->flame8_texture_img.height);

	// map_data->flame9_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/9.xpm", &map_data->flame9_texture_img.width, &map_data->flame9_texture_img.height);
	// map_data->flame9_texture_img.addr = mlx_get_data_addr(map_data->flame9_texture_img.img_ptr, &map_data->flame9_texture_img.bpp, &map_data->flame9_texture_img.line_length, &map_data->flame9_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame9_texture_img.width, map_data->flame9_texture_img.height);

	// map_data->flame10_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/10.xpm", &map_data->flame10_texture_img.width, &map_data->flame10_texture_img.height);
	// map_data->flame10_texture_img.addr = mlx_get_data_addr(map_data->flame10_texture_img.img_ptr, &map_data->flame10_texture_img.bpp, &map_data->flame10_texture_img.line_length, &map_data->flame10_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame10_texture_img.width, map_data->flame10_texture_img.height);

	// map_data->flame11_texture_img.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "textures/flame-no-bg/11.xpm", &map_data->flame11_texture_img.width, &map_data->flame11_texture_img.height);
	// map_data->flame11_texture_img.addr = mlx_get_data_addr(map_data->flame11_texture_img.img_ptr, &map_data->flame11_texture_img.bpp, &map_data->flame11_texture_img.line_length, &map_data->flame11_texture_img.endian);
	// printf(" ===================== 000000 ===================== %d %d\n", map_data->flame11_texture_img.width, map_data->flame11_texture_img.height);

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

	if (index_ogbi >= 30)
		index_ogbi = 0;
	if (index_ogbi < 10)
		flame = data->map_data->flame_texture_img;
	else if (index_ogbi < 20)
		flame = data->map_data->flame2_texture_img;
	else if (index_ogbi < 30)
		flame = data->map_data->flame3_texture_img;
	// if (index_ogbi >= 55)
	// 	index_ogbi = 0;
	// if (index_ogbi < 5)
	// 	flame = data->map_data->flame_texture_img;
	// else if (index_ogbi < 10)
	// 	flame = data->map_data->flame2_texture_img;
	// else if (index_ogbi < 15)
	// 	flame = data->map_data->flame3_texture_img;
	// else if (index_ogbi < 20)
	// 	flame = data->map_data->flame4_texture_img;
	// else if (index_ogbi < 25)
	// 	flame = data->map_data->flame5_texture_img;
	// else if (index_ogbi < 30)
	// 	flame = data->map_data->flame6_texture_img;
	// else if (index_ogbi	< 35)
	// 	flame = data->map_data->flame7_texture_img;
	// else if (index_ogbi < 40)
	// 	flame = data->map_data->flame8_texture_img;
	// else if (index_ogbi < 45)
	// 	flame = data->map_data->flame9_texture_img;
	// else if (index_ogbi < 50)
	// 	flame = data->map_data->flame10_texture_img;
	// else if (index_ogbi < 55)
	// 	flame = data->map_data->flame11_texture_img;
	data->mlx->img.width = WIDTH;
	data->mlx->img.height = HEIGHT;
	move_player(data);
	raycasting(data);
	paste_part_into_image(&flame, &data->mlx->img, (t_action){0, 0});
	mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
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

    ao_initialize();
	get_data(&data);
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	ft_init_mlx(&mlx);
	ft_init_player_position(&player, &map_data);
	load_textures(&map_data, &mlx);
	play_sound_bg(THEME);
	ft_render_map(&mlx, &map_data, &player);
	mlx_loop_hook(mlx.mlx_ptr, &ogbi, &data);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.win, 3, 1L << 1, key_realse, &data);
	mlx_hook(mlx.win, 6, 1L << 6, mouse_move, &data);
	mlx_loop(mlx.mlx_ptr);
}
