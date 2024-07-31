/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/31 12:47:44 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*   Mcros   */
// # define WIDTH 800
// # define HEIGHT 600
# define WIDTH 1000
# define HEIGHT 700
// # define MAP_NUM_ROWS 19
// # define MAP_NUM_COLS 21
# define TILE_SIZE 512
// # define TILE_SIZE 64
# define TEXT_SIZE 512
# define PI 3.14159265
# define PI_2 (PI / 2)
# define MINIMAP_SCALE 0.02
# define FOV (60 * (PI / 180)) // 60 degrees in radians
# define NUM_RAYS (WIDTH)

# define NO "textures/7it5.xpm"
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
# define W 119
# define A 97
# define S 115
# define D 100
# define T 116

/* Hooking events */
# define ON_KEYDOWN 2
# define ON_KEYUP 3

# define EPSILON 0.00001L
# define ALPHA 1

/*   Includes   */
# include "../libs/ft_containers/ft_data_structres.h"
# include "../libs/libft/libft.h"
// # include "../libs/minilibx-linux/mlx.h"
#include <mlx.h>
// #include "mlx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define RGBA 0xff000000

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

typedef struct s_action
{
	ssize_t					x;
	ssize_t					y;
}							t_action;

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

struct						s_data
{
	t_mlx					*mlx;
	t_map_data				*map_data;
	t_player				*player;
};

struct						s_mlx
{
	void					*mlx_ptr;
	void					*win;
	t_img					img;
	t_img					lkhr;
};

struct						s_player
{
	int						radius;
	// int						x;
	// int						y;
	double					x;
	double					y;
	int						turnDirection;
	int						walkDirection;
	float					rotationAngle;
	float					walkSpeed;
	float					turnSpeed;
	float					horMove;
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
	t_img					flame_texture_img;
	t_img					flame2_texture_img;
	t_img					flame3_texture_img;
	t_img					door_img;
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
	bool					wasHitVertical;
	t_point					intersection;
	double					distance;
	double					textureOffset;
	double					wallStripHeight;
	int						column;
	int						wallTop;
	int						wallBottom;
};

/*   Prototypes   */
void						ft_init_data(t_data *data);
void						ft_init_mlx(t_mlx *mlx);
void						ft_init_player_position(t_player *player,
								t_map_data *map_data);
void						my_mlx_pixel_put(t_img *img, int x, int y,
								int color);
void						draw_square(t_img *img, int x, int y, int size,
								int color);
void						ft_draw_square(t_mlx *mlx, int x, int y, int size,
								int color);
void						ft_draw_circle(t_mlx *mlx, int xc, int yc,
								int radius, int color);
void						draw_map(t_mlx *mlx, t_map_data *map_data);
void						ft_draw_line(t_mlx *mlx, int x0, int y0, int x1,
								int y1, int color);
void						raycasting(t_data *data);
bool						is_wall_1(double x, double y, t_data *data);
bool						is_wall_2(double x, double y, t_data *data);
void						cast_ray(t_data *data, t_player *player, t_ray *ray,
								double rayangle, int skip);
void						compute_ver_intercept(t_player *player, t_ray *ray,
								double *xI, double *yI);
void						compute_ver_step(t_ray *ray, double *xS,
								double *yS);
void						point_adjustment(t_point *point, t_data *data);
t_point						ver_intersection_distance(t_ray *ray,
								t_player *player, t_data *data, int skip);
t_point						hor_intersection_distance(t_ray *ray,
								t_player *player, t_data *data, int skip);

t_data						*get_data(t_data *data);
t_point						min_point(t_point a, t_point b, t_player *player);
double						distance(t_point a, t_point b);
double						normalize_angle(double angle);
// void						ft_render_map(t_mlx *mlx, t_map_data *map_data);
void						ft_render_map(t_mlx *mlx, t_map_data *map_data,
								t_player *player);
bool						equal_points(t_point a, t_point b);
void						set_ray_angle(t_ray *ray, double rayangle);
void						set_texture(t_ray *ray, t_data *data,
								t_img *texture);
void						move_player(t_data *data);
void						draw_wall(t_data *data, t_ray *ray);
void						draw_minimap(t_data *data, t_player *player);
void						draw_floor(t_data *data, int column, int wallBottom,
								double ht);
void						draw_wall_texture(t_data *data, t_ray *ray);
int							get_texel_y(t_ray *ray, int y, t_img *texture);
void						draw_ceiling(t_data *data, int column, int wallTop);
double						get_wall_height(t_data *data, t_ray *ray);
int							is_same(double a, double b);
/*   Hooks   */
int							key_press(int keycode, t_data *data);
int							key_realse(int keycode, t_data *data);
int							mouse_move(int x, int y, t_data *data);
/*   Parsing   */
void						ft_error(void);
void						skip_digits(char **line);
void						skip_whitespace(char **line);
void						check_extension(char *filename);
char						*join_splited(char **splited_line);
int							get_color(char *joined);
int							ft_atoi_rgb(char **str);
bool						is_valide_char_map(char c);
bool						is_player_in_map(char c);
bool						is_ea(char **splited);
bool						is_we(char **splited);
bool						is_so(char **splited);
bool						is_no(char **splited);
bool						is_empty_line(char final_char_line);
void						check_path(char *path);
void						add_color(int *color, char *joined, int *elemts);
void						add_path(char **identifier, char *path,
								int *elemts);
void						check_extension_textures(char *filename);
void						check_map(char **map, int nb_line, int col_len);
char						*check_line_map(char *line, bool *player_exist);
void						parsing_map(t_map_data *map_data, int fd,
								char *line);
int							max_line_len(t_lst *head);
void						read_new_line(char **splited, char **line, int fd);
void						parsing_map(t_map_data *map_data, int fd,
								char *line);
void						check_elements(char **splited, t_map_data *map_data,
								int *elemts);
void						parse_map_elements(int fd, t_map_data *map_data);
char						**ft_lst_to_map(t_lst *head);
char						**allocate_and_initialize_map(t_lst *head);
void						parse_map_file(char *file, t_map_data *map_data);
int 						clamp(int value, int min, int max);
bool						is_door(t_data *data, double x, double y, int skip);
void						handle_doors(t_data *data);
/* --------   */
/*   Mem   */
void						free_split(char **split);
#endif