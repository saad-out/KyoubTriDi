/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:13:24 by klakbuic          #+#    #+#             */
/*   Updated: 2024/06/29 11:42:55 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../libs/get_next_line/get_next_line.h"

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	skip_new_line(char **line)
{
	while (**line == '\n')
		(*line)++;
}

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}

char	*get_path(char *line)
{
	char	*path;
	int		i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		i++;
	path = (char *)malloc(sizeof(char) * (i + 1));
	if (!path)
		ft_error("Failed to allocate memory");
	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		path[i] = line[i];
		i++;
	}
	path[i] = '\0';
	return (path);
}

void	parse_map_file(char *file, t_map_data *map_data)
{
	int fd;
	char *line;
	int i;
	int j;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error("Failed to open file");
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		skip_spaces(&line);
		if (line[0] == 'N')
		{
			if (line[1] != 'O')
				ft_error();
			line += 2;
			skip_spaces(&line);
			map_data->no_texture = get_path(line);
		}
		else if (line[0] == 'S')
		{
			if (line[1] != 'O')
				ft_error();
			line += 2;
			skip_spaces(&line);
			map_data->so_texture = get_path(line);
		}
		else if (line[0] == 'W')
		{
			if (line[1] != 'E')
				ft_error();
			line += 2;
			skip_spaces(&line);
			map_data->we_texture = get_path(line);
		}
		else if (line[0] == 'E')
		{
			if (line[1] != 'A')
				ft_error();
			line += 2;
			skip_spaces(&line);
			map_data->ea_texture = get_path(line);
		}
		else if (line[0] == 'F')
		{

		}
		else if (line[0] == 'C')
		{
		}
		else if (line[0] != '\0')
		{
		} // ERROR
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}