/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 09:49:24 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	t_map_data map_data;
	// INIT:
	map_data.so_texture = NULL;
	map_data.no_texture = NULL;
	map_data.we_texture = NULL;
	map_data.ea_texture = NULL;
	map_data.ceil_color = -1;
	map_data.floor_color = -1;
	parse_map_file(av[1], &map_data);
	t_mlx mlx;
	ft_init(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
}