/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klakbuic <klakbuic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 10:43:10 by klakbuic          #+#    #+#             */
/*   Updated: 2024/07/08 09:31:26 by klakbuic         ###   ########.fr       */
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
	skip_whitespace(&line);
	while (line[i] != '\0')
	{
		if (i == ft_strlen(line) - 1 && line[i] == '\n')
			break ;
		if (!is_valide_char_map(line[i]))
			ft_error();
		i++;
	}
	return (ft_strdup(line));
}
