/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/11 11:25:57 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_square(t_mlx *mlx, int x, int y, int size, int color)
{
	for (int i = x; i < x + size; i++)
	{
		for (int j = y; j < y + size; j++)
		{
			int index = (j * WIDTH + i) * 4;
			mlx->img.addr[index] = color & 0xFF;
			mlx->img.addr[index + 1] = (color & 0xFF00) >> 8;
			mlx->img.addr[index + 2] = (color & 0xFF0000) >> 16;
		}
	}
}

void ft_draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (1) {
        // Set pixel at current (x0, y0) to the specified color
        int index = (y0 * mlx->img.line_length + x0 * (mlx->img.bpp / 8));
        mlx->img.addr[index] = color;
        mlx->img.addr[index + 1] = color >> 8;
        mlx->img.addr[index + 2] = color >> 16;

        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void ft_draw_circle(t_mlx *mlx, int xc, int yc, int radius, int color) {
    int x = radius;
    int y = 0;
    int p = 1 - radius;

    // Draw initial points on each quadrant
    ft_draw_line(mlx, xc - x, yc, xc + x, yc, color); // Initial horizontal diameter

    if (radius > 0) {
        ft_draw_square(mlx, xc - radius, yc, 1, color); // Leftmost point
        ft_draw_square(mlx, xc + radius, yc, 1, color); // Rightmost point
        ft_draw_square(mlx, xc, yc + radius, 1, color); // Topmost point
        ft_draw_square(mlx, xc, yc - radius, 1, color); // Bottommost point
    }

    // Filling the circle
    while (x > y) {
        y++;

        // Mid-point is inside or on the perimeter
        if (p <= 0) {
            p = p + 2*y + 1;
        } else { // Mid-point is outside the perimeter
            x--;
            p = p + 2*y - 2*x + 1;
        }

        // All the perimeter points have already been printed
        if (x < y) break;

        // Drawing the horizontal lines for each quadrant
        ft_draw_line(mlx, xc - x, yc + y, xc + x, yc + y, color);
        ft_draw_line(mlx, xc - x, yc - y, xc + x, yc - y, color);

        if (x != y) {
            ft_draw_line(mlx, xc - y, yc + x, xc + y, yc + x, color);
            ft_draw_line(mlx, xc - y, yc - x, xc + y, yc - x, color);
        }
    }
}

void	ft_render_player(t_mlx *mlx, t_player *player)
{
	ft_draw_circle(mlx, player->x, player->y, player->radius, 0x00065535);
	ft_draw_line(mlx, player->x, player->y, player->x + cos(player->rotationAngle) * 20,
		player->y + sin(player->rotationAngle) * 20, 0x00065535);
}

void ft_render_map(t_mlx *mlx, t_map_data *map_data)
{
		for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			if (map_data->map.map[i][j] == '1')
				ft_draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE,
					0x00FF0000);
			else if (map_data->map.map[i][j] == '0')
				ft_draw_square(mlx, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE,
					0x00FFFFFF);
		}
	}
}


int key_press(int keycode, t_data *data)
{
	if (keycode == UP_ARROW)
	{
		printf("UP\n");
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
		data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
		ft_render_map(data->mlx, data->map_data);
		data->player->rotationAngle += data->player->turnDirection * data->player->turnSpeed;
		ft_render_player(data->mlx, data->player);
		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
	}
	else if (keycode == DOWN_ARROW)
	{
		puts("DOWN");
		data->player->rotationAngle -= data->player->turnDirection * data->player->turnSpeed;
		data->player->turnDirection	
	}
	else if (keycode == LEFT_ARROW)
	{
		puts("LEFT");
	}
	else if (keycode == RIGHT_ARROW)
	{
		puts("RIGHT");
	}
	return (0);
}

int key_realse(int keycode, t_data *data)
{
	printf("Key released: %d\n", keycode);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	t_map_data map_data;
	t_player player;
	t_mlx mlx;
	t_data data;
	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;
	// INIT:
	map_data.so_texture = NULL;
	map_data.no_texture = NULL;
	map_data.we_texture = NULL;
	map_data.ea_texture = NULL;
	map_data.ceil_color = -1;
	map_data.floor_color = -1;
	parse_map_file(av[1], &map_data);
	ft_init(&mlx);
	// Render map:
	ft_render_map(&mlx, &map_data);

	// Render player:
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
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.win, 3, 1L << 1, key_realse, &data);
	mlx_loop(mlx.mlx_ptr);
}