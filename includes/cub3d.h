/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:40:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/06/24 12:23:24 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*   Mcros   */
# define WIDTH 640
# define HEIGHT 480
# define MAP_NUM_ROWS 5
# define MAP_NUM_COLS 5
# define TILE_SIZE 24

/*   Includes   */
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
typedef struct s_mlx	t_mlx;
typedef struct s_img	t_img;

/*   Structs  */
struct					s_img
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
};

struct					s_mlx
{
	void				*mlx_ptr;
	void				*win;
	t_img				img;
};

/*   Prototypes   */
void					ft_init(t_mlx *mlx);
void					my_mlx_pixel_put(t_img *img, int x, int y, int color);
void					draw_square(t_img *img, int x, int y, int size,
							int color);
#endif