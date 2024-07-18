/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/18 15:54:57 by klakbuic         ###   ########.fr       */
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

bool is_wall(int x, int y, t_data *data)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return (true);
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);
	if (mapGridIndexX < 0 || mapGridIndexX >= data->map_data->map.cols ||
		mapGridIndexY < 0 || mapGridIndexY >= data->map_data->map.rows)
		return (true);
	return (data->map_data->map.map[mapGridIndexY][mapGridIndexX] == '1');
}

float normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}
float distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
void cast_ray(t_data *data)
{
	bool found_horizontal_wall_hit = false;
	int xintercept;
	int yintercept;
	int xstep;
	int ystep;
	int next_horizontal_touch_x;
	int next_horizontal_touch_y;
	int horz_wall_hit_x = 0;
	int horz_wall_hit_y = 0;
	
	////////////////////////////////////////////
	// Horizontal ray-grid intersection code: //
	////////////////////////////////////////////
	
	// Find the y-coordinate of the closest horizontal grid intersection:
	yintercept = floor(data->player->y / TILE_SIZE) * TILE_SIZE;
	if (data->ray->is_facing_down)
		yintercept += TILE_SIZE;
	// Find the x-coordinate of the closest horizontal grid intersection:
	xintercept = data->player->x + (yintercept - data->player->y) / tan(data->ray->ray_angle);
	
	// Calculate the increment xstep and ystep:
	ystep = TILE_SIZE;
	if (data->ray->is_facing_up)
		ystep *= -1;
		
	xstep = TILE_SIZE / tan(data->ray->ray_angle);
	if (data->ray->is_facing_left && xstep > 0)
		xstep *= -1;
	if (data->ray->is_facing_right && xstep < 0)
		xstep *= -1;
	// Increment xstep and ystep until we find a wall:
	next_horizontal_touch_x = xintercept;
	next_horizontal_touch_y = yintercept;
	if (data->ray->is_facing_up)
		next_horizontal_touch_y--;
	// Increment xstep and ystep until we find a wall:
	while (next_horizontal_touch_x >= 0 && next_horizontal_touch_x < WIDTH &&
			next_horizontal_touch_y >= 0 && next_horizontal_touch_y < HEIGHT)
	{
		if (is_wall(next_horizontal_touch_x, next_horizontal_touch_y, data))
		{
			found_horizontal_wall_hit = true;
			horz_wall_hit_x = next_horizontal_touch_x;
			horz_wall_hit_y = next_horizontal_touch_y;
			break;
		}
		else
		{
			next_horizontal_touch_x += xstep;
			next_horizontal_touch_y += ystep;
		}
	}
	

	////////////////////////////////////////////
	// Vertical ray-grid intersection code: //
	////////////////////////////////////////////
	
	bool found_vertical_wall_hit = false;
	int next_vertical_touch_x;
	int next_vertical_touch_y;
	int vertical_wall_hit_x = 0;
	int vertical_wall_hit_y = 0;
	
	
	// Find the x-coordinate of the closest horizontal grid intersection:
	xintercept = floor(data->player->x / TILE_SIZE) * TILE_SIZE;
	if (data->ray->is_facing_right)
		xintercept += TILE_SIZE;
	// Find the y-coordinate of the closest horizontal grid intersection:
	yintercept = data->player->y + (xintercept - data->player->x) * tan(data->ray->ray_angle);
	
	// Calculate the increment xstep and ystep:
	xstep = TILE_SIZE;
	if (data->ray->is_facing_left)
		xstep *= -1;

	ystep = TILE_SIZE * tan(data->ray->ray_angle);
	if (data->ray->is_facing_up && ystep > 0)
		ystep *= -1;
	if (data->ray->is_facing_down && ystep < 0)
		ystep *= -1;

	// Increment xstep and ystep until we find a wall:
	next_vertical_touch_x = xintercept;
	next_vertical_touch_y = yintercept;
	
	if (data->ray->is_facing_left)
		next_vertical_touch_x--;
		
	// Increment xstep and ystep until we find a wall:
	while (next_vertical_touch_x >= 0 && next_vertical_touch_x < WIDTH &&
			next_vertical_touch_y >= 0 && next_vertical_touch_y < HEIGHT)
	{
		if (is_wall(next_vertical_touch_x, next_vertical_touch_y, data))
		{
			found_vertical_wall_hit = true;
			vertical_wall_hit_x = next_horizontal_touch_x;
			vertical_wall_hit_y = next_horizontal_touch_y;
			break;
		}
		else
		{
			next_vertical_touch_x += xstep;
			next_vertical_touch_y += ystep;
		}
	}

	// Calculate both horizontal and vertical distances and choose the smallest one:
	float horizontal_hit_distance;
	if (found_horizontal_wall_hit)
		horizontal_hit_distance = distance_between_points(data->player->x, data->player->y, horz_wall_hit_x, horz_wall_hit_y);
	else
		horizontal_hit_distance = INT_MAX;
	float vertical_hit_distance;
	if (found_vertical_wall_hit)
		vertical_hit_distance = distance_between_points(data->player->x, data->player->y, vertical_wall_hit_x, vertical_wall_hit_y);
	else
		vertical_hit_distance = INT_MAX;
	
	// Store the smallest of the two distances:
	if (horizontal_hit_distance < vertical_hit_distance)
	{
		data->ray->wall_hit_x = horz_wall_hit_x;
		data->ray->wall_hit_y = horz_wall_hit_y;
		data->ray->distance = horizontal_hit_distance;
	}
	else
	{
		data->ray->wall_hit_x = vertical_wall_hit_x;
		data->ray->wall_hit_y = vertical_wall_hit_y;
		data->ray->distance = vertical_hit_distance;
	}
}

void cast_all_rays(t_data *data)
{
	int column_id;
	t_ray *ray;

	
	column_id = 0;
	// INIT: The ray object:
	ray = data->ray;
	ray->ray_angle = normalize_angle(data->player->rotationAngle - (FOV_ANGLE / 2));
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->distance = 0;
	ray->is_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->is_facing_up = !ray->is_facing_down;
	ray->is_facing_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI;
	ray->is_facing_left = !ray->is_facing_right;
	cast_ray(data);
}

void ft_render_ray(t_mlx *mlx, t_data *data)
{
	ft_draw_line(mlx, data->player->x, data->player->y, data->ray->wall_hit_x, data->ray->wall_hit_y, 0x000000FF);
}
int key_press(int keycode, t_data *data)
{
	int next_x;
	int next_y;
	int movestep;

	if (keycode == UP_ARROW)
	{
		printf("UP\n");
		data->player->walkDirection = 1;
		movestep = data->player->walkDirection * data->player->walkSpeed;
		next_x = data->player->x + cos(data->player->rotationAngle) * movestep;
		next_y = data->player->y + sin(data->player->rotationAngle) * movestep;
		if (!is_wall(next_x, next_y, data))
		{
			puts("UP redering...");
			mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
			data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
			data->player->rotationAngle += data->player->turnDirection * data->player->turnSpeed;
			data->player->x = next_x;
			data->player->y = next_y;
			cast_all_rays(data);
			ft_render_map(data->mlx, data->map_data);
			ft_render_player(data->mlx, data->player);
			ft_render_ray(data->mlx, data);
			mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
		}
	}
	else if (keycode == DOWN_ARROW)
	{
		puts("DOWN");
		data->player->walkDirection = -1;
		movestep = data->player->walkDirection * data->player->walkSpeed;
		next_x = data->player->x + cos(data->player->rotationAngle) * movestep;
		next_y = data->player->y + sin(data->player->rotationAngle) * movestep;
		if (!is_wall(next_x, next_y, data))
		{
			printf("DOWN redering...\n");
			mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
			data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
			data->player->rotationAngle += data->player->turnDirection * data->player->turnSpeed;
			data->player->x = next_x;
			data->player->y = next_y;
			ft_render_map(data->mlx, data->map_data);
			cast_all_rays(data);
			ft_render_player(data->mlx, data->player);
			ft_render_ray(data->mlx, data);
			mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
		}
	}
	else if (keycode == LEFT_ARROW)
	{
		puts("LEFT");
		data->player->turnDirection = -1;
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
		data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
		data->player->rotationAngle += data->player->turnDirection * data->player->turnSpeed;
		cast_all_rays(data);
		ft_render_map(data->mlx, data->map_data);
		ft_render_player(data->mlx, data->player);
		ft_render_ray(data->mlx, data);
 		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
	}
	else if (keycode == RIGHT_ARROW)
	{
		puts("RIGHT");
		data->player->turnDirection = 1;
		mlx_destroy_image(data->mlx->mlx_ptr, data->mlx->img.img_ptr);
		data->mlx->img.img_ptr = mlx_new_image(data->mlx->mlx_ptr, WIDTH, HEIGHT);
		data->player->rotationAngle += data->player->turnDirection * data->player->turnSpeed;
		cast_all_rays(data);
		ft_render_map(data->mlx, data->map_data);
		ft_render_player(data->mlx, data->player);
		ft_render_ray(data->mlx, data);
 		mlx_put_image_to_window(data->mlx->mlx_ptr, data->mlx->win, data->mlx->img.img_ptr, 0, 0);
	}
	else if (keycode == ESC)
	{
		exit(0);
	}
	return (0);
}

int key_realse(int keycode, t_data *data)
{
	if (keycode == UP_ARROW)
	{
		data->player->walkDirection = 0;
	}
	else if (keycode == DOWN_ARROW)
	{
		data->player->walkDirection = 0;
	}
	else if (keycode == LEFT_ARROW)
	{
		data->player->turnDirection = 0;
	}
	else if (keycode == RIGHT_ARROW)
	{
		data->player->turnDirection = 0;
	}
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
	t_ray ray;
	t_data data;

	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;
	data.ray = &ray;
	// INIT:
	map_data.so_texture = NULL;
	map_data.no_texture = NULL;
	map_data.we_texture = NULL;
	map_data.ea_texture = NULL;
	map_data.ceil_color = -1;
	map_data.floor_color = -1;
	// INIT:
	map_data.map.rows = 21;
	map_data.map.cols = 21;
	parse_map_file(av[1], &map_data);
	ft_init(&mlx);

	// INIT player:
	player.x = WIDTH / 8;
	player.y = HEIGHT / 8 + 3;
	player.radius = 7;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = PI / 2;
	player.walkSpeed = 10;
	player.turnSpeed = 10 * (PI / 180);

	// INIT ray:
	ray.ray_angle = normalize_angle(player.rotationAngle - (FOV_ANGLE / 2));
	ray.wall_hit_x = 0;
	ray.wall_hit_y = 0;
	ray.distance = 0;
	ray.is_facing_down = ray.ray_angle > 0 && ray.ray_angle < PI;
	ray.is_facing_up = !ray.is_facing_down;
	ray.is_facing_right = ray.ray_angle < 0.5 * PI || ray.ray_angle > 1.5 * PI;
	ray.is_facing_left = !ray.is_facing_right;
	
	ft_render_map(&mlx, &map_data);
	ft_render_player(&mlx, &player);
	// ft_render_ray(&mlx, &data);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
	mlx_hook(mlx.win, 3, 1L << 1, key_realse, &data);
	mlx_loop(mlx.mlx_ptr);
}