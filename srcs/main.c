/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 10:10:27 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	paste_part_into_image(t_img *img1, t_img *img2, int x, int y)
{
	int				i;
	int				j;
	unsigned int	*img1_addr;
	unsigned int	*img2_addr;

	i = 0;
	img1_addr = (unsigned int *)img1->addr;
	img2_addr = (unsigned int *)img2->addr;
	while (i < img1->height)
	{
		j = 0;
		while (j < img1->width)
		{
			if (img1_addr[j + i * img1->width] != BG && (x + j) < WIDTH && (i
					+ y) < HEIGHT)
				img2_addr[(x + j) + ((i + y) * (img2->width))] = img1_addr[j + i
					* img1->width];
			j++;
		}
		i++;
	}
}

t_data	*get_data(t_data *data)
{
	static t_data	*tmp = NULL;

	if (data)
		tmp = data;
	return (tmp);
}

int	main(int ac, char **av)
{
	t_map_data	map_data;
	t_player	player;
	t_mlx		mlx;
	t_data		data;

	if (ac != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	get_data(&data);
	running_threads(INIT, 0);
	ao_initialize();
	ft_init_mlx(&mlx);
	ft_init_player_position(&player, &map_data);
	load_textures(&map_data, &mlx);
	ft_init_lock(&data);
	theme_sound(THEME);
	setup_hooks(&data);
	mlx_loop_hook(mlx.mlx_ptr, &render_frame, &data);
	mlx_loop(mlx.mlx_ptr);
}
