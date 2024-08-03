/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/03 15:17:28 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_render_map(t_render_map *map, t_player *player)
{
	map->view_distance = 5;
	map->player_x = player->x / TILE_SIZE;
	map->player_y = player->y / TILE_SIZE;
	map->start_x = map->player_x - map->view_distance;
	map->start_y = map->player_y - map->view_distance;
	map->end_x = map->player_x + map->view_distance;
	map->end_y = map->player_y + map->view_distance;
}

void	init_start_x_y(t_render_map *map, t_map_data *map_data)
{
	while (map->start_x < 0)
	{
		map->start_x++;
		if (map->end_x < map_data->map.cols)
			map->end_x++;
	}
	while (map->start_y < 0)
	{
		map->start_y++;
		if (map->end_y < map_data->map.rows)
			map->end_y++;
	}
	while (map->end_x > map_data->map.cols)
	{
		map->end_x--;
		if (map->start_x > 0)
			map->start_x--;
	}
	while (map->end_y > map_data->map.rows)
	{
		map->end_y--;
		if (map->start_y > 0)
			map->start_y--;
	}
}

void	render_squres(t_mlx *mlx, t_render_map *map, t_map_data *map_data,
		int i, int j)
{
	if (map_data->map.map[i][j] == '1')
		ft_draw_square(mlx, map->offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
			map->offsety * (int)(TILE_SIZE * MINIMAP_SCALE), (int)(TILE_SIZE
				* MINIMAP_SCALE), 0x00666340);
	else if (map_data->map.map[i][j] == '2')
		ft_draw_square(mlx, map->offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
			map->offsety * (int)(TILE_SIZE * MINIMAP_SCALE), (int)(TILE_SIZE
				* MINIMAP_SCALE), 0x000000FF);
	else if (map_data->map.map[i][j] == '3')
		ft_draw_square(mlx, map->offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
			map->offsety * (int)(TILE_SIZE * MINIMAP_SCALE), (int)(TILE_SIZE
				* MINIMAP_SCALE), 0x0000FF00);
	else if (map_data->map.map[i][j] != ' ')
		ft_draw_square(mlx, map->offsetx * (int)(TILE_SIZE * MINIMAP_SCALE),
			map->offsety * (int)(TILE_SIZE * MINIMAP_SCALE), (int)(TILE_SIZE
				* MINIMAP_SCALE), 0x808080);
}

void	render_map(t_mlx *mlx, t_render_map *map, t_map_data *map_data)
{
	int	i;
	int	j;

	map->offsety = 0;
	i = map->start_y;
	while (i < map->end_y)
	{
		map->offsetx = 0;
		j = map->start_x;
		while (j < map->end_x)
		{
			render_squres(mlx, map, map_data, i, j);
			if (i == (int)map->player_y && j == (int)map->player_x)
			{
				map->imran_x = map->offsetx;
				map->imran_y = map->offsety;
			}
			map->offsetx++;
			j++;
		}
		map->offsety++;
		i++;
	}
}

void	ft_render_map(t_mlx *mlx, t_map_data *map_data, t_player *player)
{
	int				posx;
	int				posy;
	t_render_map	map;
	t_draw_line		line;

	init_render_map(&map, player);
	init_start_x_y(&map, map_data);
	map.offsety = 0;
	render_map(mlx, &map, map_data);
	posx = (map.imran_x + map.player_x - (int)map.player_x) * TILE_SIZE;
	posy = (map.imran_y + map.player_y - (int)map.player_y) * TILE_SIZE;
	// to handle draw circle:
	// ft_draw_circle(mlx, posx * MINIMAP_SCALE, posy * MINIMAP_SCALE,
	// 	player->radius * MINIMAP_SCALE, 0x283fd1);
	ft_draw_square(mlx, posx * MINIMAP_SCALE, posy * MINIMAP_SCALE,
		player->radius * 0.05, 0x283fd1);
	line.x0 = posx * MINIMAP_SCALE;
	line.y0 = posy * MINIMAP_SCALE;
	line.x1 = (posx + cos(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE;
	line.y1 = (posy + sin(player->rotationAngle) * TILE_SIZE) * MINIMAP_SCALE;
	line.color = 0x283fd1;
	ft_draw_line(mlx,  &line);
}

void	paste_part_into_image(t_img *img1, t_img *img2, int x, int y)
{
	int				i;
	int				j;
	unsigned int	*img1_addr;
	unsigned int	*img2_addr;

	i = 0;
	img1_addr = (unsigned int *)img1->addr;
	img2_addr = (unsigned int *)img2->addr;
	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			if (img1_addr[j + i * img1->width] != BG \
				&& (x + j) < WIDTH && (i + y) < HEIGHT)
				img2_addr[(x + j) + ((i + y) * (img2->width))] \
				= img1_addr[j + i * img1->width];
			j++;
		}
		i++;
	}
}

t_data	*get_data(t_data *data)
{
	static t_data	*tmp = NULL;

	if (data)
		tmp = data;
	return (tmp);
}

int	main(int ac, char **av)
{
	t_map_data map_data;
	t_player player;
	t_mlx mlx;
	t_data data;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	get_data(&data);
	running_threads(INIT, 0);
    ao_initialize();
	ft_init_mlx(&mlx);
	ft_init_player_position(&player, &map_data);
	load_textures(&map_data, &mlx);
	ft_init_lock(&data);
	theme_sound(THEME);
	setup_hooks(&data);
	mlx_loop_hook(mlx.mlx_ptr, &render_frame, &data);
	mlx_loop(mlx.mlx_ptr);
}
