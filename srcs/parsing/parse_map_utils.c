/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:05:44 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/04 12:54:45 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/get_next_line.h"

void	read_new_line(char **splited, char **line, int fd)
{
	free_split(splited);
	free(*line);
	*line = get_next_line(fd);
}

char	**ft_lst_to_map(t_lst *head)
{
	char	*line;
	char	**map;
	t_lst	*lst;
	int		i;
	int		j;

	map = allocate_and_initialize_map(head);
	i = -1;
	lst = head;
	while (++i < (int)ft_lstsize(head))
	{
		j = -1;
		while (++j < max_line_len(head))
		{
			line = lst->content;
			if (j < (int)ft_strlen(line))
				map[i][j] = line[j];
			if (map[i][j] == 'D')
				map[i][j] = '2';
		}
		lst = (t_lst *)lst->next;
	}
	map[i] = NULL;
	return (map);
}

void	parsing_map(t_map_data *map_data, int fd, char *line)
{
	t_lst	*head;
	char	*line_map;
	bool	player_exist;

	player_exist = false;
	head = NULL;
	map_data->map.rows = 0;
	while (line)
	{
		line_map = check_line_map(line, &player_exist);
		ft_lstadd_back(&head, ft_lstnew(line_map));
		free(line);
		line = get_next_line(fd);
		map_data->map.rows++;
	}
	if (map_data->map.rows < 3)
		ft_error();
	if (!player_exist)
		ft_error();
	map_data->map.map = ft_lst_to_map(head);
	check_map(map_data->map.map, ft_lstsize(head), max_line_len(head));
	map_data->map.cols = max_line_len(head);
	ft_lstclear(&head, free);
}

void	check_elements(char **splited, t_map_data *map_data, int *elemts)
{
	if (is_no(splited))
		add_path(&map_data->no_texture, splited[1], elemts);
	else if (is_so(splited))
		add_path(&map_data->so_texture, splited[1], elemts);
	else if (is_we(splited))
		add_path(&map_data->we_texture, splited[1], elemts);
	else if (is_ea(splited))
		add_path(&map_data->ea_texture, splited[1], elemts);
	else if (ft_strcmp(splited[0], "F") == 0 && splited[1])
		add_color(&map_data->floor_color, join_splited(splited), elemts);
	else if (ft_strcmp(splited[0], "C") == 0 && splited[1])
		add_color(&map_data->ceil_color, join_splited(splited), elemts);
	else
		ft_error();
}

void	parse_map_elements(int fd, t_map_data *map_data)
{
	char	*line;
	char	**splited;
	int		elemts;

	elemts = 0;
	line = get_next_line(fd);
	while (line)
	{
		splited = ft_split(line, ' ');
		if (elemts == 6 && splited[0] && splited[0][0] == '1')
		{
			free_split(splited);
			break ;
		}
		else if (splited[0] == NULL || is_empty_line(splited[0][0]))
		{
			read_new_line(splited, &line, fd);
			continue ;
		}
		check_elements(splited, map_data, &elemts);
		read_new_line(splited, &line, fd);
	}
	if (elemts != 6 || !line)
		ft_error();
	parsing_map(map_data, fd, line);
}
