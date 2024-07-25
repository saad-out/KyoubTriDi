/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/24 05:41:13 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*   Mcros   */
# define WIDTH 800
# define HEIGHT 600
// # define MAP_NUM_ROWS 19
// # define MAP_NUM_COLS 21
# define TILE_SIZE 512
// # define TILE_SIZE 64
# define TEXT_SIZE 512
# define PI 3.14159265
# define MINIMAP_SCALE 0.02
# define FOV (60 * (PI / 180)) // 60 degrees in radians
# define NUM_RAYS (WIDTH)

# define NO "textures/pornhub.xpm"
# define SO "textures/7it2.xpm"
# define WE "textures/7itakhor.xpm"
# define EA "textures/7it3.xpm"

/* PRINTF COLORS */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

/*   KEYS    */
# define ESC 65307
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

/* Hooking events */
# define ON_KEYDOWN 2
# define ON_KEYUP 3

#define EPSILON 0.00001L

/*   Includes   */
# include "../libs/ft_containers/ft_data_structres.h"
# include "../libs/libft/libft.h"
// # include "../libs/minilibx-linux/mlx.h"
// # include "../libs/minilibx-linux/mlx.h"
#include <mlx.h>
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
	int						width;
	int						height;	
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
	// int						x;
	// int						y;
	double						x;
	double						y;
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
	t_img					no_texture_img;
	t_img					so_texture_img;
	t_img					we_texture_img;
	t_img					ea_texture_img;
	t_map_grid				map;
};

struct						s_point
{
	double	x;
	double	y;
};

struct						s_ray
{
	double	angle;
	bool	facingUp;
	bool	facingRight;
	bool	wasHitVertical;
	t_point	intersection;
	double	distance;
	double	textureOffset;
};

/*   Prototypes   */
void						ft_init_mlx(t_mlx *mlx);
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);
void						draw_square(t_img *img, int x, int y, int size,
								int color);
void ft_draw_circle(t_mlx *mlx, int xc, int yc, int radius, int color);
void						draw_map(t_mlx *mlx, t_map_data *map_data);
void						ft_draw_line(t_mlx *mlx, int x0, int y0, int x1,
								int y1, int color);
void						cast_rays(t_mlx *mlx, t_player *player);
// bool						is_wall(int x, int y, t_data *data);
bool						is_wall(double x, double y, t_data *data, int flag);

t_data	*get_data(t_data *data);
t_point min_point(t_point a, t_point b, t_player *player);
double distance(t_point a, t_point b);
double  normalizeAngle(double angle);
void ft_render_map(t_mlx *mlx, t_map_data *map_data);
bool equal_points(t_point a, t_point b);
void	set_ray_angle(t_ray	*ray);
void	set_texture(t_ray ray, t_data *data, t_img *texture);

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