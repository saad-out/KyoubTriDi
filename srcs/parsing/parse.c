
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
	puts("Before print the map: =====================");
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
	puts("After print the map: =====================");
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
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		lst = (t_lst *)lst->next;
		i++;
	}
	printf("HELLO\n");
	map[i] = NULL;
	return (map);
}

void check_map(char **map, int nb_line, int col_len)
{
	int i;
	int j;

	i = 0;
	while (i < nb_line)
	{
		j = 0;
		while (j < col_len)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E') {
				if (i == 0 || i == nb_line - 1 || j == 0 || j == col_len - 1)
					ft_error();
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					ft_error();
			}
			j++;
		}
		i++;
	}
}

void	parse_map_file(char *file, t_map_data *map_data)
{
	int		fd;
	char	*line;
	char	**splited_line;
	int		count_elements;
	t_lst	*head;

	check_extension(file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error();
	line = get_next_line(fd);
	count_elements = 0;
	while (line)
	{
		splited_line = ft_split(line, ' ');
		if (count_elements == 6 && splited_line[0] && splited_line[0][0] == '1')
		{
			puts("break =====================");
			break ;
		}
		else if (splited_line[0] == NULL || splited_line[0][0] == '\n'
			|| splited_line[0][0] == '\0')
		{
			free_split(splited_line);
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		else if (ft_strcmp(splited_line[0], "NO") == 0 && splited_line[1])
		{
			// Check for the path with open
			if (map_data->no_texture)
				ft_error();
			map_data->no_texture = ft_strdup(splited_line[1]);
			count_elements++;
		}
		else if (ft_strcmp(splited_line[0], "SO") == 0 && splited_line[1])
		{
			// Check for the path with open
			if (map_data->so_texture)
				ft_error();
			map_data->so_texture = ft_strdup(splited_line[1]);
			count_elements++;
		}
		else if (ft_strcmp(splited_line[0], "WE") == 0 && splited_line[1])
		{
			// Check for the path with open
			if (map_data->we_texture)
				ft_error();
			map_data->we_texture = ft_strdup(splited_line[1]);
			count_elements++;
		}
		else if (ft_strcmp(splited_line[0], "EA") == 0 && splited_line[1])
		{
			// Check for the path with open
			if (map_data->ea_texture)
				ft_error();
			map_data->ea_texture = ft_strdup(splited_line[1]);
			count_elements++;
		}
		else if (ft_strcmp(splited_line[0], "F") == 0 && splited_line[1])
		{
			if (map_data->floor_color != -1)
				ft_error();
			map_data->floor_color = get_color(join_splited(splited_line));
			count_elements++;
		}
		else if (ft_strcmp(splited_line[0], "C") == 0 && splited_line[1])
		{
			if (map_data->ceil_color != -1)
				ft_error();
			map_data->ceil_color = get_color(join_splited(splited_line));
			count_elements++;
		}
		else
		{
			ft_error();
		}
		free_split(splited_line);
		free(line);
		line = get_next_line(fd);
	}
	// Start parsing the map
	head = NULL;
	while (line)
	{
		char *tmp;
		tmp = check_line_map(line);
		printf("tmp: |%s|\n", tmp);
		ft_lstadd_back(&head, ft_lstnew(tmp));
		free(line);
		line = get_next_line(fd);
	}
	map_data->map.map = ft_lst_to_map(head);
	check_map(map_data->map.map, ft_lstsize(head), max_line_len(head));
	ft_lstclear(&head, free);
	close(fd);
}
