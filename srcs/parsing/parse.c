/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:26:16 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/30 12:26:55 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/get_next_line.h"

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

bool	is_valide_identifier(char *identifier)
{
	if (ft_strcmp(identifier, "NO") == 0 || ft_strcmp(identifier, "SO") == 0
		|| ft_strcmp(identifier, "WE") == 0 || ft_strcmp(identifier, "EA") == 0
		|| ft_strcmp(identifier, "F") == 0 || ft_strcmp(identifier, "C") == 0)
		return (true);
	return (false);
}

char	**allocate_and_initialize_map(t_lst *head)
{
	char	**map;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!map)
		ft_error();
	i = 0;
	while (i < ft_lstsize(head))
	{
		map[i] = (char *)malloc(sizeof(char) * max_line_len(head));
		i++;
	}
	i = 0;
	while (i < ft_lstsize(head))
	{
		j = 0;
		while (j < max_line_len(head))
		{
			map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (map);
}

void	parse_map_file(char *file, t_map_data *map_data)
{
	int	fd;

	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	parse_map_elements(fd, map_data);
	close(fd);
}
