/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:09:48 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/06 10:22:47 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	int r;
	int g;
	int b;
	int t;
	char **line;

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