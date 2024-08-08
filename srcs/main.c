/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutchak <soutchak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 12:46:50 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/09 00:53:53 by soutchak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cub3d(t_data *data)
{
	running_threads(INIT, 0);
	ao_initialize();
	ft_init_mlx(data->mlx);
	ft_init_player_position(data->player, data->map_data);
	load_textures(data->map_data, data->mlx);
	ft_init_lock(data);
	theme_sound(THEME);
	setup_hooks(data);
	mlx_loop_hook(data->mlx->mlx_ptr, &render_frame, data);
	mlx_loop(data->mlx->mlx_ptr);
}

int	main(int ac, char **av)
{
	t_map_data	map_data;
	t_player	player;
	t_mlx		mlx;
	t_data		data;

	if (ac != 2)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	data.mlx = &mlx;
	data.map_data = &map_data;
	data.player = &player;
	ft_init_data(&data);
	parse_map_file(av[1], &map_data);
	get_data(&data);
	cub3d(&data);
}
