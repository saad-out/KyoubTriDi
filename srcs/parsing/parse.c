
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

int	max_line_len(t_lst *head)
{
	t_lst	*lst;
	int		max_len;
	int		len;

	lst = head;
	max_len = 0;
	while (lst)
	{
		len = ft_strlen(lst->content);
		if (len > max_len)
			max_len = len;
		lst = (t_lst *)lst->next;
	}
	return (max_len);
}

char	**ft_lst_to_map(t_lst *head)
{
	char	*line;
	char	**map;
	t_lst	*lst;
	int		i;
	int		j;

	map = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!map)
		ft_error();
	i = 0;
	while (i < ft_lstsize(head))
		map[i++] = (char *)malloc(sizeof(char) * max_line_len(head));
	i = 0;
	j = 0;
	// puts("Before print the map: =====================");
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
	// puts("After print the map: =====================");
	// print the map:
	i = 0;
	j = 0;
	lst = head;
	while (i < ft_lstsize(head))
	{
		j = 0;
		while (j < max_line_len(head))
		{
			line = lst->content;
			if (j < ft_strlen(line))
				map[i][j] = line[j];
			// printf("%c", map[i][j]);
			j++;
		}
		// printf("\n");
		lst = (t_lst *)lst->next;
		i++;
	}
	printf("HELLO\n");
	map[i] = NULL;
	return (map);
}

void	check_map(char **map, int nb_line, int col_len)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_line)
	{
		j = 0;
		while (j < col_len)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
			{
				if (i == 0 || i == nb_line - 1 || j == 0 || j == col_len - 1)
					ft_error();
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
					ft_error();
			}
			j++;
		}
		i++;
	}
}

void	check_extension_textures(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".xpm") != 0)
		ft_error();
}

bool	is_empty_line(char final_char_line)
{
	if (final_char_line == '\n' || final_char_line == '\0')
		return (true);
	return (false);
}

void	add_path(char **identifier, char *path, int *elemts)
{
	check_path(path);
	if (*identifier)
		ft_error();
	*identifier = ft_strdup(path);
	(*elemts)++;
}
void	add_color(int *color, char *joined, int *elemts)
{
	if (*color != -1)
		ft_error();
	*color = get_color(joined);
	(*elemts)++;
}

void	read_new_line(char **splited, char **line, int fd)
{
	free_split(splited);
	free(*line);
	*line = get_next_line(fd);
}

void	parsing_map(t_map_data *map_data, int fd)
{
	t_lst	*head;
	char	*line;
	char	*tmp;

	head = NULL;
	map_data->map.rows = 0;
	while (line)
	{
		tmp = check_line_map(line);
		ft_lstadd_back(&head, ft_lstnew(tmp));
		free(line);
		line = get_next_line(fd);
		map_data->map.rows++;
	}
	map_data->map.map = ft_lst_to_map(head);
	check_map(map_data->map.map, ft_lstsize(head), max_line_len(head));
	map_data->map.cols = max_line_len(head);
	ft_lstclear(&head, free);
}

void	parse_map_file(char *file, t_map_data *map_data)
{
	int		fd;
	char	*line;
	char	**splited;
	int		elemts;

	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	elemts = 0;
	line = get_next_line(fd);
	while (line)
	{
		splited = ft_split(line, ' ');
		if (elemts == 6 && splited[0] && splited[0][0] == '1')
		{
			break ;
		}
		else if (splited[0] == NULL || is_empty_line(splited[0][0]))
		{
			read_new_line(splited, &line, fd);
			continue ;
		}
		else if (ft_strcmp(splited[0], "NO") == 0 && splited[1])
		{
			add_path(&map_data->no_texture, splited[1], &elemts);
		}
		else if (ft_strcmp(splited[0], "SO") == 0 && splited[1])
		{
			add_path(&map_data->so_texture, splited[1], &elemts);
		}
		else if (ft_strcmp(splited[0], "WE") == 0 && splited[1])
		{
			add_path(&map_data->we_texture, splited[1], &elemts);
		}
		else if (ft_strcmp(splited[0], "EA") == 0 && splited[1])
		{
			add_path(&map_data->ea_texture, splited[1], &elemts);
		}
		else if (ft_strcmp(splited[0], "F") == 0 && splited[1])
		{
			add_color(&map_data->floor_color, join_splited(splited),
				&elemts);
		}
		else if (ft_strcmp(splited[0], "C") == 0 && splited[1])
		{
			add_color(&map_data->ceil_color, join_splited(splited), &elemts);
		}
		else
		{
			ft_error();
		}
		read_new_line(splited, &line, fd);
	}
	if (elemts != 6 || !line)
		ft_error();
	// Start parsing the map:
	parsing_map(map_data, fd);
	close(fd);
}
