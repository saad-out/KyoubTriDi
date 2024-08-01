/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:50:17 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/01 17:50:50 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_flames(t_map_data *md, t_mlx *mlx)
{
	md->txt.flame[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F1, \
													&md->txt.flame[0].width, \
													&md->txt.flame[0].height);
	md->txt.flame[0].addr = mlx_get_data_addr(md->txt.flame[0].img_ptr, \
											&md->txt.flame[0].bpp, \
											&md->txt.flame[0].line_length, \
											&md->txt.flame[0].endian);
	md->txt.flame[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F2, \
													&md->txt.flame[1].width, \
													&md->txt.flame[1].height);
	md->txt.flame[1].addr = mlx_get_data_addr(md->txt.flame[1].img_ptr, \
											&md->txt.flame[1].bpp, \
											&md->txt.flame[1].line_length, \
											&md->txt.flame[1].endian);
	md->txt.flame[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F3, \
													&md->txt.flame[2].width, \
													&md->txt.flame[2].height);
	md->txt.flame[2].addr = mlx_get_data_addr(md->txt.flame[2].img_ptr, \
											&md->txt.flame[2].bpp, \
											&md->txt.flame[2].line_length, \
											&md->txt.flame[2].endian);
}

void	load_no_ea(t_map_data *md, t_mlx *mlx)
{
	md->txt.walls[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													md->no_texture, \
													&md->txt.walls[0].width, \
													&md->txt.walls[0].height);
	md->txt.walls[0].addr = mlx_get_data_addr(md->txt.walls[0].img_ptr, \
											&md->txt.walls[0].bpp, \
											&md->txt.walls[0].line_length, \
											&md->txt.walls[0].endian);
	md->txt.walls[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													md->ea_texture, \
													&md->txt.walls[1].width, \
													&md->txt.walls[1].height);
	md->txt.walls[1].addr = mlx_get_data_addr(md->txt.walls[1].img_ptr, \
											&md->txt.walls[1].bpp, \
											&md->txt.walls[1].line_length, \
											&md->txt.walls[1].endian);
}

void	load_so_we(t_map_data *md, t_mlx *mlx)
{
	md->txt.walls[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													md->so_texture, \
													&md->txt.walls[2].width, \
													&md->txt.walls[2].height);
	md->txt.walls[2].addr = mlx_get_data_addr(md->txt.walls[2].img_ptr, \
											&md->txt.walls[2].bpp, \
											&md->txt.walls[2].line_length, \
											&md->txt.walls[2].endian);
	md->txt.walls[3].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													md->we_texture, \
													&md->txt.walls[3].width, \
													&md->txt.walls[3].height);
	md->txt.walls[3].addr = mlx_get_data_addr(md->txt.walls[3].img_ptr, \
											&md->txt.walls[3].bpp, \
											&md->txt.walls[3].line_length, \
											&md->txt.walls[3].endian);
}

void	load_walls(t_map_data *md, t_mlx *mlx)
{
	load_no_ea(md, mlx);
	load_so_we(md, mlx);
}

void	load_textures(t_map_data *md, t_mlx *mlx)
{
	md->txt.door.img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													DOOR, \
													&md->txt.door.width, \
													&md->txt.door.height);
	md->txt.door.addr = mlx_get_data_addr(md->txt.door.img_ptr, \
												&md->txt.door.bpp, \
												&md->txt.door.line_length, \
												&md->txt.door.endian);
	load_flames(md, mlx);
	load_walls(md, mlx);
}
