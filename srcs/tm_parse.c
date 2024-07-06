// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/06/29 11:13:24 by klakbuic          #+#    #+#             */
// /*   Updated: 2024/07/01 15:38:38 by klakbuic         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/cub3d.h"
// #include "../includes/get_next_line.h"


// void	ft_error(void)
// {
// 	printf("Error\n");
// 	exit(EXIT_FAILURE);
// }

// void	skip_new_line(char **line)
// {
// 	while (**line == '\n')
// 		(*line)++;
// }

// void	skip_spaces(char **line)
// {
// 	while (**line == ' ')
// 		(*line)++;
// }

// char	*get_path(char *line)
// {
// 	char	*path;
// 	int		i;

// 	i = 0;
// 	while (line[i] != '\0' && line[i] != ' ')
// 		i++;
// 	path = (char *)malloc(sizeof(char) * (i + 1));
// 	if (!path)
// 		ft_error();
// 	i = 0;
// 	while (line[i] != '\0' && line[i] != ' ')
// 	{
// 		path[i] = line[i];
// 		i++;
// 	}
// 	path[i] = '\0';
// 	return (path);
// }

// void	check_valide_number(int color)
// {
// 	if (!(0 <= color && color <= 255))
// 		ft_error();
// }

// void skip_digits(char **line)
// {
// 	while (ft_isdigit(**line) || **line == ' ')
// 		(*line)++;
	
// }

// int	get_color(char **line)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	int	t;

// 	t = 0;
// 	r = ft_atoi(*line);
// 	check_valide_number(r);
// 	skip_digits(line);
// 	if (**line == ',')
// 		(*line)++;
// 	else
// 		ft_error();
// 	skip_spaces(line);
// 	g = ft_atoi(*line);
// 	check_valide_number(r);
// 	skip_digits(line);
// 	if (**line == ',')
// 		(*line)++;
// 	else
// 		ft_error();
// 	b = ft_atoi(*line);
// 	check_valide_number(b);
// 	return (t << 24 | r << 16 | g << 8 | b);
// }

// // void skip_spaces_new_line(char **line)
// // {
// // 	while (**line == ' ' || **line == '\n')
// // 		(*line)++;
// // }

// void check_extension(char *file)
// {
// 	int i;

// 	i = 0;
// 	while (file[i] != '\0')
// 		i++;
// 	if (file[i - 1] != 'b' || file[i - 2] != 'u' || file[i - 3] != 'c' || file[i - 4] != '.')
// 		ft_error();
// }

// void check_all_is_walls(char *line)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] != '1' && line[i] != ' ')
// 			ft_error();
// 		i++;
// 	}
// }

// void	parse_map_file(char *file, t_map_data *map_data)
// {
// 	int fd;
// 	char *line;
// 	int i;
// 	int j;
// 	int counter_elements;

// 	check_extension(file);
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		ft_error();
// 	i = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		skip_spaces(&line);
// 		if (line[0] == 'N')
// 		{
// 			if (line[1] != 'O')
// 				ft_error();
// 			line += 2;
// 			skip_spaces(&line);
// 			map_data->no_texture = get_path(line);
// 			++counter_elements;
// 		}
// 		else if (line[0] == 'S')
// 		{
// 			if (line[1] != 'O')
// 				ft_error();
// 			line += 2;
// 			skip_spaces(&line);
// 			map_data->so_texture = get_path(line);
// 			++counter_elements;
// 		}
// 		else if (line[0] == 'W')
// 		{
// 			if (line[1] != 'E')
// 				ft_error();
// 			line += 2;
// 			skip_spaces(&line);
// 			m	ap_data->we_texture = get_path(line);
// 			++counter_elements;
// 		}
// 		else if (line[0] == 'E')
// 		{
// 			if (line[1] != 'A')
// 				ft_error();
// 			line += 2;
// 			skip_spaces(&line);
// 			map_data->ea_texture = get_path(line);
// 			++counter_elements;
// 		}
// 		else if (line[0] == 'F')
// 		{
// 			line++;
// 			skip_spaces(&line);
// 			map_data->floor_color = get_color(&line);
// 			++counter_elements;
// 		}
// 		else if (line[0] == 'C')
// 		{
// 			line++;
// 			skip_spaces(&line);
// 			map_data->ceil_color = get_color(&line);
// 			++counter_elements;
// 		}
// 		else if (line[0] != '\0')
// 			ft_error();
// 		free(line);
// 		line = get_next_line(fd);
// 		if (counter_elements == 6)
// 			break;
// 	}
	
// 	while (line)
// 	{
// 		skip_spaces(&line);
// 		if (line[0] != '\0')
// 			break;
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	t_list *head = NULL;
// 	size_t max_len = 0;
// 	while (line)
// 	{
// 		//trim the end spaces !!!!!!!!!
// 		size_t curr_len = ft_strlen(line);
// 		if (max_len < curr_len)
// 			max_len = curr_len;
// 		ft_lstadd_back(&head, ft_lstnew(line));
// 		free(line);
// 		line = get_next_line(fd);	
// 	}
// 	// build the 2D map of the game
// 	map_data->map.map = (char **)malloc(sizeof(char *) * ft_lstsize(head));
		
// 	printf("NO: %s\n", map_data->no_texture);
// 	printf("SO: %s\n", map_data->so_texture);
// 	printf("WE: %s\n", map_data->we_texture);
// 	printf("EA: %s\n", map_data->ea_texture);
// 	printf("F: %d\n", map_data->floor_color);
// 	printf("C: %d\n", map_data->ceil_color);
// 	close(fd);
// }