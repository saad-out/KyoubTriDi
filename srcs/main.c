/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/01 17:50:52 by soutchak         ###   ########.fr       */
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
	ft_draw_line(
		mlx,
		posx * MINIMAP_SCALE,
		posy * MINIMAP_SCALE,
		(posx + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		(posy + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE,
		0x283fd1);
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

int	ogbi(void *d)
{
	t_data *data = (t_data *)d;

	if (index_ogbi >= 30)
		index_ogbi = 0;
	if (index_ogbi < 10)
		flame = data->map_data->txt.flame[0];
	else if (index_ogbi < 20)
		flame = data->map_data->txt.flame[1];
	else if (index_ogbi < 30)
		flame = data->map_data->txt.flame[2];
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
	setup_hooks(&data);
	mlx_loop_hook(mlx.mlx_ptr, &ogbi, &data);
	mlx_loop(mlx.mlx_ptr);
}
