/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/20 11:59:09 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*   Mcros   */
# define WIDTH 800
# define HEIGHT 800
# define MAP_NUM_ROWS 19
# define MAP_NUM_COLS 21
# define TILE_SIZE 32
# define PI 3.14159265
# define MINIMAP_SCALE 0.4
# define FOV (60 * (PI / 180)) // 60 degrees in radians
# define WALL_STRIP_WIDTH 1
# define NUM_RAYS (WIDTH / WALL_STRIP_WIDTH)
# define TEX_WIDTH 32
# define TEX_HEIGHT 32
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
typedef struct s_point		t_point;
typedef struct s_ray		t_ray;

/*   Structs  */
struct						s_data
{
	t_mlx					*mlx;
	t_map_data				*map_data;
	t_player				*player;
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

struct						s_point
{
	double					x;
	double					y;
};

struct						s_ray
{
	double					angle;
	bool					facingUp;
	bool					facingRight;
	t_point					intersection;
	double					distance;
};

/*   Prototypes   */
void						ft_init_mlx(t_mlx *mlx);
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);
void						draw_square(t_img *img, int x, int y, int size,
								int color);
void						draw_map(t_mlx *mlx, t_map_data *map_data);
void						ft_draw_line(t_mlx *mlx, int x0, int y0, int x1,
								int y1, int color);
void						cast_rays(t_mlx *mlx, t_player *player);
bool						is_wall(int x, int y, t_data *data);

t_data						*get_data(t_data *data);
t_point						min_point(t_point a, t_point b, t_player *player);
double						distance(t_point a, t_point b);
double						normalizeAngle(double angle);
void						ft_render_map(t_mlx *mlx, t_map_data *map_data);

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