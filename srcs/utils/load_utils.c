/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/03 15:19:17 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_last_flame(t_map_data *md, t_mlx *mlx)
{
	md->txt.flame[2].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F3, \
													&md->txt.flame[2].width, \
													&md->txt.flame[2].height);
	if (md->txt.flame[2].img_ptr == NULL)
		ft_error();
	md->txt.flame[2].addr = mlx_get_data_addr(md->txt.flame[2].img_ptr, \
											&md->txt.flame[2].bpp, \
											&md->txt.flame[2].line_length, \
											&md->txt.flame[2].endian);
}

void	load_flames(t_map_data *md, t_mlx *mlx)
{
	md->txt.flame[0].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F1, \
													&md->txt.flame[0].width, \
													&md->txt.flame[0].height);
	if (md->txt.flame[0].img_ptr == NULL)
		ft_error();
	md->txt.flame[0].addr = mlx_get_data_addr(md->txt.flame[0].img_ptr, \
											&md->txt.flame[0].bpp, \
											&md->txt.flame[0].line_length, \
											&md->txt.flame[0].endian);
	md->txt.flame[1].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													F2, \
													&md->txt.flame[1].width, \
													&md->txt.flame[1].height);
	if (md->txt.flame[1].img_ptr == NULL)
		ft_error();
	md->txt.flame[1].addr = mlx_get_data_addr(md->txt.flame[1].img_ptr, \
											&md->txt.flame[1].bpp, \
											&md->txt.flame[1].line_length, \
											&md->txt.flame[1].endian);
	load_last_flame(md, mlx);
}
