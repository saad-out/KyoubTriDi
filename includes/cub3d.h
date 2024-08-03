/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/03 15:21:06 by soutchak         ###   ########.fr       */
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

# define DOOR "textures/creepydoor.xpm"
# define F1 "textures/1bg.xpm"
# define F2 "textures/2bg.xpm"
# define F3 "textures/3bg.xpm"

// # define OPEN_DOOR "sounds/fbi-open-the-door.mp3"
# define OPEN_DOOR "sounds/open2.mp3"
# define CLOSE_DOOR "sounds/close.mp3"
# define THEME "sounds/haunted.mp3"

# define ADD 0
# define STOP 1
# define INIT 2
# define MAX_THREADS 10000

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
# define PLAYER_SIZE 30

# define BG 0xff000000

/*   Includes   */
# include "../libs/ft_containers/ft_data_structres.h"
# include "../libs/libft/libft.h"
// # include "../libs/minilibx-linux/mlx.h"
#include <mlx.h>
// #include "mlx/mlx.h"
# include <ao/ao.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mpg123.h>
# include <pthread.h>
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
typedef struct s_sound		t_sound;
typedef struct s_rgb		t_rgb;
typedef struct s_textures	t_textures;
typedef struct s_render_map	t_render_map;
typedef struct s_draw_line	t_draw_line;
typedef struct s_exit		t_exit;

/*   Structs  */

struct						s_draw_line
{
	int						x0;
	int						y0;
	int						x1;
	int						y1;
	int						dx;
	int						dy;
	int						sx;
	int						sy;
	int						color;
};

struct						s_render_map
{
	double					player_x;
	double					player_y;
	int						start_x;
	int						start_y;
	int						end_x;
	int						end_y;
	int						imran_x;
	int						imran_y;
	int						view_distance;
	int						offsetx;
	int						offsety;
};

struct						s_rgb
{
	int						red;
	int						green;
	int						blue;
};

struct						s_sound
{
	mpg123_handle			*mh;
	unsigned char			*buffer;
	size_t					buffer_size;
	size_t					done;
	int						driver;
	ao_device				*dev;
};

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

struct						s_exit
{
	pthread_mutex_t			mutex;
	bool					flag;
};

struct						s_data
{
	t_mlx					*mlx;
	t_map_data				*map_data;
	t_player				*player;
	t_exit					quit;
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

struct						s_textures
{
	t_img					walls[4];
	t_img					flame[3];
	t_img					door;
};

struct						s_map_data
{
	int						ceil_color;
	int						floor_color;
	char					*no_texture;
	char					*so_texture;
	char					*we_texture;
	char					*ea_texture;
	t_textures				txt;
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
// void						ft_draw_line(t_mlx *mlx, int x0, int y0, int x1,
// 								int y1, int color);
void						ft_draw_line(t_mlx *mlx, t_draw_line *line);
void						raycasting(t_data *data);
bool						is_wall_1(double x, double y, t_data *data);
bool						is_wall_2(double x, double y, t_data *data);
void						cast_ray(t_data *data, t_ray *ray, double rayangle,
								int skip);
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
void						draw_floor(t_data *data, int column, int wallBottom);
void						draw_wall_texture(t_data *data, t_ray *ray);
int							get_texel_y(t_ray *ray, int y, t_img *texture);
void						draw_ceiling(t_data *data, int column, int wallTop);
double						get_wall_height(t_data *data, t_ray *ray);
/*   Hooks   */
int							key_press(int keycode, t_data *data);
int							key_realse(int keycode, t_data *data);
int							mouse_move(int x, int y, t_data *data);
void						setup_hooks(t_data *data);
/*   Parsing   */
void						ft_error(void);
void						skip_digits(char **line);
void						skip_whitespace(char **line);
void						check_extension(char *filename);
char						*join_splited(char **splited_line);
int							get_color(char *joined);
int							ft_atoi_rgb(char **str);
bool						is_valide_char_map(char c);
bool						player_exist(char c);
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
int							clamp(int value, int min, int max);
bool						cannot_move(double x, double y, t_data *data);
bool						is_door(t_data *data, double x, double y, int skip);
void						handle_doors(t_data *data);
void						*play_mp3(void *arg);
void						play_sound_bg(char *mp3);
void						load_textures(t_map_data *md, t_mlx *mlx);
int							render_frame(void *d);
void						paste_part_into_image(t_img *img1, t_img *img2,
								int x, int y);
void						ft_init_lock(t_data *data);
bool						quit_program(t_data *data);
void						set_exit_flag(t_data *data);
t_data						*get_data(t_data *data);
void						running_threads(int action, pthread_t thread);
void						theme_sound(char *mp3);
void						load_flames(t_map_data *md, t_mlx *mlx);
/* --------   */
/*   Mem   */
void						free_split(char **split);
void						free_all_mem(t_data *data);
#endif