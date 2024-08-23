/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:19:01 by soutchak          #+#    #+#             */
/*   Updated: 2024/08/23 01:42:47 by soutchak         ###   ########.fr       */
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
	char *s[SPRITE_FRAMES] = {
		"textures/lkhr/1.xpm",
		"textures/lkhr/2.xpm",
		"textures/lkhr/3.xpm",
		"textures/lkhr/4.xpm",
		"textures/lkhr/5.xpm",
		"textures/lkhr/6.xpm",
		"textures/lkhr/7.xpm",
		"textures/lkhr/8.xpm",
		"textures/lkhr/9.xpm",
		"textures/lkhr/10.xpm",
		"textures/lkhr/11.xpm",
		"textures/lkhr/12.xpm",
		"textures/lkhr/13.xpm",
		"textures/lkhr/14.xpm",
		"textures/lkhr/15.xpm",
		"textures/lkhr/16.xpm",
		"textures/lkhr/17.xpm",
		"textures/lkhr/18.xpm",
		"textures/lkhr/19.xpm",
		"textures/lkhr/20.xpm",
		"textures/lkhr/21.xpm",
		"textures/lkhr/22.xpm",
		"textures/lkhr/23.xpm",
		"textures/lkhr/24.xpm",
		"textures/lkhr/25.xpm",
		"textures/lkhr/26.xpm",
		"textures/lkhr/27.xpm",
		"textures/lkhr/28.xpm",
		"textures/lkhr/29.xpm",
		"textures/lkhr/30.xpm",
		"textures/lkhr/31.xpm",
		"textures/lkhr/32.xpm",
		"textures/lkhr/33.xpm",
		"textures/lkhr/34.xpm",
		"textures/lkhr/35.xpm",
		"textures/lkhr/36.xpm",
		"textures/lkhr/37.xpm",
		"textures/lkhr/38.xpm",
		"textures/lkhr/39.xpm",
		"textures/lkhr/40.xpm"
	};
	for (int i = 0; i < SPRITE_FRAMES; i++)
	{
		md->txt.flame[i].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, \
													s[i], \
													&md->txt.flame[i].width, \
													&md->txt.flame[i].height);
		if (md->txt.flame[i].img_ptr == NULL)
			ft_error();
		md->txt.flame[i].addr = mlx_get_data_addr(md->txt.flame[i].img_ptr, \
												&md->txt.flame[i].bpp, \
												&md->txt.flame[i].line_length, \
												&md->txt.flame[i].endian);
	}
}
