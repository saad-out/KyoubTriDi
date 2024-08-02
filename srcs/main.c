/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/02 10:28:20 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	static t_data *tmp = NULL;

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
	get_data(&data);
	running_threads(INIT, 0);
    ao_initialize();
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	ft_init_mlx(&mlx);
	ft_init_player_position(&player, &map_data);
	load_textures(&map_data, &mlx);
	ft_init_lock(&data);
	play_sound_bg(THEME);
	ft_render_map(&mlx, &map_data, &player);
	setup_hooks(&data);
	mlx_loop_hook(mlx.mlx_ptr, &render_frame, &data);
	mlx_loop(mlx.mlx_ptr);
}
