/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/18 11:17:42 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*   Mcros   */
# define WIDTH 800
# define HEIGHT 800
# define MAP_NUM_ROWS 21
# define MAP_NUM_COLS 21
# define TILE_SIZE 32
# define PI 3.14159265
# define TWO_PI (PI * 2)
# define FOV_ANGLE (60 * (PI / 180))
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS (WIDTH / WALL_STRIP_WIDTH)

/*   KEYS    */
# define ESC 65307
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

/* Hooking events */
# define ON_KEYDOWN 2
# define ON_KEYUP 3
/*   Includes   */
# include "../libs/ft_containers/ft_data_structres.h"
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/*   Typedefs   */
typedef struct s_data		t_data;
typedef struct s_mlx		t_mlx;
typedef struct s_img		t_img;
typedef struct s_player		t_player;
typedef struct s_map_data	t_map_data;
typedef struct s_map_grid	t_map_grid;
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;

/*   Structs  */
struct						s_data
{
	t_mlx					*mlx;
	t_map_data				*map_data;
	t_player				*player;
	t_ray					*ray;
};

struct						s_img
{
	void					*img_ptr;
	char					*addr;
	int						bpp;
	int						line_length;
	int						endian;
};

struct						s_mlx
{
	void					*mlx_ptr;
	void					*win;
	t_img					img;
};

struct						s_player
{
	int						radius;
	int						x;
	int						y;
	int						turnDirection;
	int						walkDirection;
	float					rotationAngle;
	float					walkSpeed;
	float					turnSpeed;
};

struct						s_ray
{
	float					ray_angle;
	float					wall_hit_x;
	float					wall_hit_y;
	float					distance;
	bool					is_facing_down;
	bool					is_facing_up;
	bool					is_facing_right;
	bool					is_facing_left;
};

struct						s_map_grid
{
	int						rows;
	int						cols;
	char					**map;
};

struct						s_map_data
{
	int						ceil_color;
	int						floor_color;
	char					*no_texture;
	char					*so_texture;
	char					*we_texture;
	char					*ea_texture;
	t_map_grid				map;
};

/*   Prototypes   */
void						ft_init(t_mlx *mlx);
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);
void						draw_square(t_img *img, int x, int y, int size,
								int color);
void						draw_map(t_mlx *mlx, t_map_data *map_data);

/*   Parsing   */
void						ft_error(void);
void						skip_digits(char **line);
void						skip_whitespace(char **line);
void						check_extension(char *filename);
char						*join_splited(char **splited_line);
int							get_color(char *joined);
int							ft_atoi_rgb(char **str);
bool						is_valide_char_map(char c);
char						*check_line_map(char *line);
void						parse_map_file(char *file, t_map_data *map_data);
/* --------   */
/*   Mem   */
void						free_split(char **split);
#endif