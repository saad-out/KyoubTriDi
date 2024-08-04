/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:32:39 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 10:08:04 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	render_squres(t_data *data, t_render_map *map, int i, int j)
{
	t_draw_square	square;

	square.x = map->offsetx * (int)(TILE_SIZE * MINIMAP_SCALE);
	square.y = map->offsety * (int)(TILE_SIZE * MINIMAP_SCALE);
	square.size = (int)(TILE_SIZE * MINIMAP_SCALE);
	square.color = 0x00666340;
	if (data->map_data->map.map[i][j] == '1')
		ft_draw_square(data->mlx, &square);
	else if (data->map_data->map.map[i][j] == '2')
	{
		square.color = 0x000000FF;
		ft_draw_square(data->mlx, &square);
	}
	else if (data->map_data->map.map[i][j] == '3')
	{
		square.color = 0x0000FF00;
		ft_draw_square(data->mlx, &square);
	}
	else if (data->map_data->map.map[i][j] != ' ')
	{
		square.color = 0x808080;
		ft_draw_square(data->mlx, &square);
	}
}

void	render_map(t_data *data, t_render_map *map)
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
			render_squres(data, map, i, j);
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

void	ft_render_map(t_data *data)
{
	int				posx;
	int				posy;
	t_render_map	map;
	t_draw_line		line;
	t_draw_square	square;

	init_render_map(&map, data->player);
	init_start_x_y(&map, data->map_data);
	map.offsety = 0;
	render_map(data, &map);
	posx = (map.imran_x + map.player_x - (int)map.player_x) * TILE_SIZE;
	posy = (map.imran_y + map.player_y - (int)map.player_y) * TILE_SIZE;
	square.x = posx * MINIMAP_SCALE;
	square.y = posy * MINIMAP_SCALE;
	square.size = data->player->radius * 0.05;
	square.color = 0x283fd1;
	ft_draw_square(data->mlx, &square);
	line.x0 = posx * MINIMAP_SCALE + data->player->radius * 0.05 / 2;
	line.y0 = posy * MINIMAP_SCALE + data->player->radius * 0.05 / 2;
	line.x1 = (posx + cos(data->player->rotationAngle) * TILE_SIZE)
		* MINIMAP_SCALE;
	line.y1 = (posy + sin(data->player->rotationAngle) * TILE_SIZE)
		* MINIMAP_SCALE;
	line.color = 0x283fd1;
	ft_draw_line(data->mlx, &line);
}
