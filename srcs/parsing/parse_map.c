/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:43:10 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/08 15:02:15 by klakbuic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_valide_char_map(char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E')
		return (true);
	return (false);
}

char	*check_line_map(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (i == ft_strlen(line) - 1 && line[i] == '\n')
		{
			line[i] = '\0';
			break ;
		}
		if (!is_valide_char_map(line[i]))
			ft_error();
		i++;
	}
	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == ' ')
		line[i--] = '\0';
	return (ft_strdup(line));
}
