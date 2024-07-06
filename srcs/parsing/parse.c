
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:20:59 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/03 09:45:24 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/get_next_line.h"

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	skip_whitespace(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

void	check_extension(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
		i++;
	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i
		- 4] != '.')
		ft_error();
}

void	skip_digits(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
}

char	*join_splited(char **splited_line)
{
	int		i;
	char	*joined;
	char	*tmp;

	i = 1;
	joined = NULL;
	while (splited_line[i])
	{
		tmp = joined;
		joined = ft_strjoin(joined, splited_line[i]);
		if (tmp)
			free(tmp);
		i++;
	}
	return (joined);
}

int	get_color(char *joined)
{
	int		r;
	int		g;
	int		b;
	int		t;
	char	**line;

	line = &joined;
	t = 0;
	r = ft_atoi_rgb(line);
	skip_whitespace(line);
	if (**line == ',')
		(*line)++;
	else
		ft_error();
	g = ft_atoi_rgb(line);
	skip_whitespace(line);
	if (**line == ',')
		(*line)++;
	else
		ft_error();
	b = ft_atoi_rgb(line);
	return (t << 24 | r << 16 | g << 8 | b);
}

void	parse_map_file(char *file, t_map_data *map_data)
{
	int fd;
	char *line;
	char **splited_line;

	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	line = get_next_line(fd);
	while (line)
	{
		splited_line = ft_split(line, ' ');
		if (splited_line[0] == NULL)
		{
			free_split(splited_line);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (ft_strcmp(splited_line[0], "NO") == 0 && splited_line[1])
		{
			// Check for the path with open
			map_data->no_texture = ft_strdup(splited_line[1]);
		}
		else if (ft_strcmp(splited_line[0], "SO") == 0 && splited_line[1])
		{
			// Check for the path with open
			map_data->so_texture = ft_strdup(splited_line[1]);
		}
		else if (ft_strcmp(splited_line[0], "WE") == 0 && splited_line[1])
		{
			// Check for the path with open
			map_data->we_texture = ft_strdup(splited_line[1]);
		}
		else if (ft_strcmp(splited_line[0], "EA") == 0 && splited_line[1])
		{
			// Check for the path with open
			map_data->ea_texture = ft_strdup(splited_line[1]);
		}
		else if (ft_strcmp(splited_line[0], "F") == 0 && splited_line[1])
		{
			map_data->floor_color = get_color(join_splited(splited_line));
		}
		else if (ft_strcmp(splited_line[0], "C") == 0 && splited_line[1])
		{
			map_data->ceil_color = get_color(join_splited(splited_line));		
		}
		free_split(splited_line);
		free(line);
		line = get_next_line(fd);
	}
	printf("NO: %s\n", map_data->no_texture);
	printf("SO: %s\n", map_data->so_texture);
	printf("WE: %s\n", map_data->we_texture);
	printf("EA: %s\n", map_data->ea_texture);
	printf("F: %d\n", map_data->floor_color);
	printf("C: %d\n", map_data->ceil_color);
	close(fd);
}