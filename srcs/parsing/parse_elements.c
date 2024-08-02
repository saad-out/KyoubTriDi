/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:09:48 by klakbuic          #+#    #+#             */
/*   Updated: 2024/08/02 11:53:43 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_whitespace_linefeed(char **line)
{
	while (**line == ' ' || **line == '\t' || **line == '\n')
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
	char *tmp;
	char	**line;

	tmp = joined;
	line = &joined;
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
	if (**line != '\0' && **line != '\n')
		ft_error();
	free(tmp);
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	check_extension_textures(char *filename)
{
	int	i;
	int	len;

	i = 0;
	while (filename[i] && filename[i] != '\n')
		i++;
	filename[i] = '\0';
	len = ft_strlen(filename);
	if (len < 4 || ft_strcmp(filename + len - 4, ".xpm") != 0)
		ft_error();
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error();
	close(fd);
}
